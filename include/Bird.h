class Bird {
public:
    Bird();

    void flap();

    void calcPhysics(float);

private:
    float fPosition;
    float fVelocity;
    float fAcceleration;
    float fWeight;
};
