#include "stdafx.h"

#include "Particle.h"


inline float Deg2Rad(float a)
{
    return a * 0.01745329252f;
}

inline float Rad2Deg(float a)
{
    return a * 57.29577951f;
}

inline float clampf(float value, float min_inclusive, float max_inclusive)
{
    if (min_inclusive > max_inclusive)
    {
        std::swap(min_inclusive, max_inclusive);
    }
    return value < min_inclusive ? min_inclusive : value < max_inclusive ? value : max_inclusive;
}

inline void normalize_point(float x, float y, Pointf* out)
{
    float n = x * x + y * y;
    // Already normalized.
    if (n == 1.0f)
    {
        return;
    }

    n = sqrt(n);
    // Too close to zero.
    if (n < 1e-5)
    {
        return;
    }

    n = 1.0f / n;
    out->x = x * n;
    out->y = y * n;
}

/**
A more effect random number getter function, get from ejoy2d.
*/
inline static float RANDOM_M11(unsigned int* seed)
{
    *seed = *seed * 134775813 + 1;
    union
    {
        uint32_t d;
        float f;
    } u;
    u.d = (((uint32_t)(*seed) & 0x7fff) << 8) | 0x40000000;
    return u.f - 3.0f;
}

Particle::Particle()
{
    this->isParticle = true;
}

// implementation Particle

bool Particle::initWithTotalParticles(int numberOfParticles)
{
    _totalParticles = numberOfParticles;
    _isActive = true;
    _emitterMode = Mode::GRAVITY;
    _isAutoRemoveOnFinish = false;
    _transformSystemDirty = false;

    resetTotalParticles(numberOfParticles);

    return true;
}

void Particle::resetTotalParticles(int numberOfParticles)
{
    if (particle_data_.size() < numberOfParticles)
    {
        particle_data_.resize(numberOfParticles);
    }
}

Particle::~Particle()
{
}

void Particle::addParticles(int count)
{
    if (_paused)
    {
        return;
    }
    uint32_t RANDSEED = rand();

    int start = _particleCount;
    _particleCount += count;

    //life
    for (int i = start; i < _particleCount; ++i)
    {
        float theLife = _life + _lifeVar * RANDOM_M11(&RANDSEED);
        particle_data_[i].timeToLive = (std::max)(0.0f, theLife);
    }

    //position
    for (int i = start; i < _particleCount; ++i)
    {
        particle_data_[i].posx = _sourcePosition.x + _posVar.x * RANDOM_M11(&RANDSEED);
    }

    for (int i = start; i < _particleCount; ++i)
    {
        particle_data_[i].posy = _sourcePosition.y + _posVar.y * RANDOM_M11(&RANDSEED);
    }

    //color
#define SET_COLOR(c, b, v)                                                 \
    for (int i = start; i < _particleCount; ++i)                           \
    {                                                                      \
        particle_data_[i].c = clampf(b + v * RANDOM_M11(&RANDSEED), 0, 1); \
    }

    SET_COLOR(colorR, _startColor.r, _startColorVar.r);
    SET_COLOR(colorG, _startColor.g, _startColorVar.g);
    SET_COLOR(colorB, _startColor.b, _startColorVar.b);
    SET_COLOR(colorA, _startColor.a, _startColorVar.a);

    SET_COLOR(deltaColorR, _endColor.r, _endColorVar.r);
    SET_COLOR(deltaColorG, _endColor.g, _endColorVar.g);
    SET_COLOR(deltaColorB, _endColor.b, _endColorVar.b);
    SET_COLOR(deltaColorA, _endColor.a, _endColorVar.a);

#define SET_DELTA_COLOR(c, dc)                                                                              \
    for (int i = start; i < _particleCount; ++i)                                                            \
    {                                                                                                       \
        particle_data_[i].dc = (particle_data_[i].dc - particle_data_[i].c) / particle_data_[i].timeToLive; \
    }

    SET_DELTA_COLOR(colorR, deltaColorR);
    SET_DELTA_COLOR(colorG, deltaColorG);
    SET_DELTA_COLOR(colorB, deltaColorB);
    SET_DELTA_COLOR(colorA, deltaColorA);

    //size
    for (int i = start; i < _particleCount; ++i)
    {
        particle_data_[i].size = _startSize + _startSizeVar * RANDOM_M11(&RANDSEED);
        particle_data_[i].size = (std::max)(0.0f, particle_data_[i].size);
    }

    if (_endSize != START_SIZE_EQUAL_TO_END_SIZE)
    {
        for (int i = start; i < _particleCount; ++i)
        {
            float endSize = _endSize + _endSizeVar * RANDOM_M11(&RANDSEED);
            endSize = (std::max)(0.0f, endSize);
            particle_data_[i].deltaSize = (endSize - particle_data_[i].size) / particle_data_[i].timeToLive;
        }
    }
    else
    {
        for (int i = start; i < _particleCount; ++i)
        {
            particle_data_[i].deltaSize = 0.0f;
        }
    }

    // rotation
    for (int i = start; i < _particleCount; ++i)
    {
        particle_data_[i].rotation = _startSpin + _startSpinVar * RANDOM_M11(&RANDSEED);
    }
    for (int i = start; i < _particleCount; ++i)
    {
        float endA = _endSpin + _endSpinVar * RANDOM_M11(&RANDSEED);
        particle_data_[i].deltaRotation = (endA - particle_data_[i].rotation) / particle_data_[i].timeToLive;
    }

    // position
    Vec2 pos;
    pos.x = x_;
    pos.y = y_;

    for (int i = start; i < _particleCount; ++i)
    {
        particle_data_[i].startPosX = pos.x;
    }
    for (int i = start; i < _particleCount; ++i)
    {
        particle_data_[i].startPosY = pos.y;
    }

    // Mode Gravity: A
    if (_emitterMode == Mode::GRAVITY)
    {

        // radial accel
        for (int i = start; i < _particleCount; ++i)
        {
            particle_data_[i].modeA.radialAccel = modeA.radialAccel + modeA.radialAccelVar * RANDOM_M11(&RANDSEED);
        }

        // tangential accel
        for (int i = start; i < _particleCount; ++i)
        {
            particle_data_[i].modeA.tangentialAccel = modeA.tangentialAccel + modeA.tangentialAccelVar * RANDOM_M11(&RANDSEED);
        }

        // rotation is dir
        if (modeA.rotationIsDir)
        {
            for (int i = start; i < _particleCount; ++i)
            {
                float a = Deg2Rad(_angle + _angleVar * RANDOM_M11(&RANDSEED));
                Vec2 v(cosf(a), sinf(a));
                float s = modeA.speed + modeA.speedVar * RANDOM_M11(&RANDSEED);
                Vec2 dir = v * s;
                particle_data_[i].modeA.dirX = dir.x;    //v * s ;
                particle_data_[i].modeA.dirY = dir.y;
                particle_data_[i].rotation = -Rad2Deg(dir.getAngle());
            }
        }
        else
        {
            for (int i = start; i < _particleCount; ++i)
            {
                float a = Deg2Rad(_angle + _angleVar * RANDOM_M11(&RANDSEED));
                Vec2 v(cosf(a), sinf(a));
                float s = modeA.speed + modeA.speedVar * RANDOM_M11(&RANDSEED);
                Vec2 dir = v * s;
                particle_data_[i].modeA.dirX = dir.x;    //v * s ;
                particle_data_[i].modeA.dirY = dir.y;
            }
        }
    }

    // Mode Radius: B
    else
    {
        for (int i = start; i < _particleCount; ++i)
        {
            particle_data_[i].modeB.radius = modeB.startRadius + modeB.startRadiusVar * RANDOM_M11(&RANDSEED);
        }

        for (int i = start; i < _particleCount; ++i)
        {
            particle_data_[i].modeB.angle = Deg2Rad(_angle + _angleVar * RANDOM_M11(&RANDSEED));
        }

        for (int i = start; i < _particleCount; ++i)
        {
            particle_data_[i].modeB.degreesPerSecond = Deg2Rad(modeB.rotatePerSecond + modeB.rotatePerSecondVar * RANDOM_M11(&RANDSEED));
        }

        if (modeB.endRadius == START_RADIUS_EQUAL_TO_END_RADIUS)
        {
            for (int i = start; i < _particleCount; ++i)
            {
                particle_data_[i].modeB.deltaRadius = 0.0f;
            }
        }
        else
        {
            for (int i = start; i < _particleCount; ++i)
            {
                float endRadius = modeB.endRadius + modeB.endRadiusVar * RANDOM_M11(&RANDSEED);
                particle_data_[i].modeB.deltaRadius = (endRadius - particle_data_[i].modeB.radius) / particle_data_[i].timeToLive;
            }
        }
    }
}

void Particle::stopSystem()
{
    _isActive = false;
    _elapsed = _duration;
    _emitCounter = 0;
}

void Particle::resetSystem()
{
    _isActive = true;
    _elapsed = 0;
    for (int i = 0; i < _particleCount; ++i)
    {
        //particle_data_[i].timeToLive = 0.0f;
    }
}

bool Particle::isFull()
{
    return (_particleCount == _totalParticles);
}

// ParticleSystem - MainLoop
void Particle::update()
{
    float dt = 1.0 / 25;
    if (_isActive && _emissionRate)
    {
        float rate = 1.0f / _emissionRate;
        int totalParticles = _totalParticles;

        //issue #1201, prevent bursts of particles, due to too high emitCounter
        if (_particleCount < totalParticles)
        {
            _emitCounter += dt;
            if (_emitCounter < 0.f)
            {
                _emitCounter = 0.f;
            }
        }

        int emitCount = (std::min)(1.0f * (totalParticles - _particleCount), _emitCounter / rate);
        addParticles(emitCount);
        _emitCounter -= rate * emitCount;

        _elapsed += dt;
        if (_elapsed < 0.f)
        {
            _elapsed = 0.f;
        }
        if (_duration != DURATION_INFINITY && _duration < _elapsed)
        {
            this->stopSystem();
        }
    }

    for (int i = 0; i < _particleCount; ++i)
    {
        particle_data_[i].timeToLive -= dt;
    }

    // rebirth
    for (int i = 0; i < _particleCount; ++i)
    {
        if (particle_data_[i].timeToLive <= 0.0f)
        {
            int j = _particleCount - 1;
            //while (j > 0 && particle_data_[i].timeToLive <= 0)
            //{
            //    _particleCount--;
            //    j--;
            //}
            particle_data_[i] = particle_data_[_particleCount - 1];
            --_particleCount;
        }
    }

    if (_emitterMode == Mode::GRAVITY)
    {
        for (int i = 0; i < _particleCount; ++i)
        {
            Pointf tmp, radial = { 0.0f, 0.0f }, tangential;

            // radial acceleration
            if (particle_data_[i].posx || particle_data_[i].posy)
            {
                normalize_point(particle_data_[i].posx, particle_data_[i].posy, &radial);
            }
            tangential = radial;
            radial.x *= particle_data_[i].modeA.radialAccel;
            radial.y *= particle_data_[i].modeA.radialAccel;

            // tangential acceleration
            std::swap(tangential.x, tangential.y);
            tangential.x *= -particle_data_[i].modeA.tangentialAccel;
            tangential.y *= particle_data_[i].modeA.tangentialAccel;

            // (gravity + radial + tangential) * dt
            tmp.x = radial.x + tangential.x + modeA.gravity.x;
            tmp.y = radial.y + tangential.y + modeA.gravity.y;
            tmp.x *= dt;
            tmp.y *= dt;

            particle_data_[i].modeA.dirX += tmp.x;
            particle_data_[i].modeA.dirY += tmp.y;

            // this is cocos2d-x v3.0
            // if (_configName.length()>0 && _yCoordFlipped != -1)

            // this is cocos2d-x v3.0
            tmp.x = particle_data_[i].modeA.dirX * dt * _yCoordFlipped;
            tmp.y = particle_data_[i].modeA.dirY * dt * _yCoordFlipped;
            particle_data_[i].posx += tmp.x;
            particle_data_[i].posy += tmp.y;
        }
    }
    else
    {
        for (int i = 0; i < _particleCount; ++i)
        {
            particle_data_[i].modeB.angle += particle_data_[i].modeB.degreesPerSecond * dt;
            particle_data_[i].modeB.radius += particle_data_[i].modeB.deltaRadius * dt;
            particle_data_[i].posx = -cosf(particle_data_[i].modeB.angle) * particle_data_[i].modeB.radius;
            particle_data_[i].posy = -sinf(particle_data_[i].modeB.angle) * particle_data_[i].modeB.radius * _yCoordFlipped;
        }
    }

    //color, size, rotation
    for (int i = 0; i < _particleCount; ++i)
    {
        particle_data_[i].colorR += particle_data_[i].deltaColorR * dt;
        particle_data_[i].colorG += particle_data_[i].deltaColorG * dt;
        particle_data_[i].colorB += particle_data_[i].deltaColorB * dt;
        particle_data_[i].colorA += particle_data_[i].deltaColorA * dt;
        particle_data_[i].size += (particle_data_[i].deltaSize * dt);
        particle_data_[i].size = (std::max)(0.0f, particle_data_[i].size);
        particle_data_[i].rotation += particle_data_[i].deltaRotation * dt;
    }
}

// ParticleSystem - Properties of Gravity Mode
void Particle::setTangentialAccel(float t)
{
    modeA.tangentialAccel = t;
}

float Particle::getTangentialAccel() const
{
    return modeA.tangentialAccel;
}

void Particle::setTangentialAccelVar(float t)
{
    modeA.tangentialAccelVar = t;
}

float Particle::getTangentialAccelVar() const
{
    return modeA.tangentialAccelVar;
}

void Particle::setRadialAccel(float t)
{
    modeA.radialAccel = t;
}

float Particle::getRadialAccel() const
{
    return modeA.radialAccel;
}

void Particle::setRadialAccelVar(float t)
{
    modeA.radialAccelVar = t;
}

float Particle::getRadialAccelVar() const
{
    return modeA.radialAccelVar;
}

void Particle::setRotationIsDir(bool t)
{
    modeA.rotationIsDir = t;
}

bool Particle::getRotationIsDir() const
{
    return modeA.rotationIsDir;
}

void Particle::setGravity(const Vec2& g)
{
    modeA.gravity = g;
}

const Vec2& Particle::getGravity()
{
    return modeA.gravity;
}

void Particle::setSpeed(float speed)
{
    modeA.speed = speed;
}

float Particle::getSpeed() const
{
    return modeA.speed;
}

void Particle::setSpeedVar(float speedVar)
{

    modeA.speedVar = speedVar;
}

float Particle::getSpeedVar() const
{

    return modeA.speedVar;
}

// ParticleSystem - Properties of Radius Mode
void Particle::setStartRadius(float startRadius)
{
    modeB.startRadius = startRadius;
}

float Particle::getStartRadius() const
{
    return modeB.startRadius;
}

void Particle::setStartRadiusVar(float startRadiusVar)
{
    modeB.startRadiusVar = startRadiusVar;
}

float Particle::getStartRadiusVar() const
{
    return modeB.startRadiusVar;
}

void Particle::setEndRadius(float endRadius)
{
    modeB.endRadius = endRadius;
}

float Particle::getEndRadius() const
{
    return modeB.endRadius;
}

void Particle::setEndRadiusVar(float endRadiusVar)
{
    modeB.endRadiusVar = endRadiusVar;
}

float Particle::getEndRadiusVar() const
{

    return modeB.endRadiusVar;
}

void Particle::setRotatePerSecond(float degrees)
{
    modeB.rotatePerSecond = degrees;
}

float Particle::getRotatePerSecond() const
{
    return modeB.rotatePerSecond;
}

void Particle::setRotatePerSecondVar(float degrees)
{
    modeB.rotatePerSecondVar = degrees;
}

float Particle::getRotatePerSecondVar() const
{
    return modeB.rotatePerSecondVar;
}

bool Particle::isActive() const
{
    return _isActive;
}

int Particle::getTotalParticles() const
{
    return _totalParticles;
}

void Particle::setTotalParticles(int var)
{
    _totalParticles = var;
}

vector<ParticleData> Particle::getParticleDataVector() const
{
    return particle_data_;
}

bool Particle::isAutoRemoveOnFinish() const
{
    return _isAutoRemoveOnFinish;
}

void Particle::setAutoRemoveOnFinish(bool var)
{
    _isAutoRemoveOnFinish = var;
}

////don't use a transform matrix, this is faster
//void Particle::setScale(float s)
//{
//    _transformSystemDirty = true;
//    Node::setScale(s);
//}
//
//void Particle::setRotation(float newRotation)
//{
//    _transformSystemDirty = true;
//    Node::setRotation(newRotation);
//}
//
//void Particle::setScaleX(float newScaleX)
//{
//    _transformSystemDirty = true;
//    Node::setScaleX(newScaleX);
//}
//
//void Particle::setScaleY(float newScaleY)
//{
//    _transformSystemDirty = true;
//    Node::setScaleY(newScaleY);
//}

bool Particle::isPaused() const
{
    return _paused;
}

void Particle::pauseEmissions()
{
    _paused = true;
}

void Particle::resumeEmissions()
{
    _paused = false;
}
