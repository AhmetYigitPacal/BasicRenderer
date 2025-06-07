#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
public:
    Transform() = default;
    Transform(const Transform& other) : position_(other.position_), scale_(other.scale_), rotation_(other.rotation_) {}

    glm::vec3 position() { return position_; }

    void setPosition(glm::vec3 position) { position_ = position; }
    void setPosition(float x, float y, float z) { position_ = glm::vec3(x, y, z); }

    void translate(glm::vec3 position) { position_ += position; }
    void translate(float x, float y, float z) { position_ += glm::vec3(x, y, z); }


    glm::vec3 scale() { return scale_; }

    void setScale(glm::vec3 scale) { scale_ = scale; }
    void setScale(float x, float y, float z) { scale_ = glm::vec3(x, y, z); }

    void scaleBy(glm::vec3 scale) { scale_ *= scale; }
    void scaleBy(float x, float y, float z) { scale_ *= glm::vec3(x, y, z); }
    void scaleBy(float s) { scale_ *= glm::vec3(s); }


    glm::quat rotation() { return rotation_; }

    void setRotation(glm::quat rotation) { rotation_ = rotation; }

    void rotate(float angle, glm::vec3 axis) {
        rotation_ = glm::angleAxis(glm::radians(angle), axis) * rotation_;
        rotation_ = glm::normalize(rotation_);
    }

    void rotateAround(float angle, glm::vec3 point, glm::vec3 axis) {
        glm::vec3 relativePos = position_ - point;
        glm::quat rotationQuat = glm::angleAxis(glm::radians(angle), axis);
        relativePos = rotationQuat * relativePos;
        position_ = relativePos + point;

        rotation_ = rotationQuat * rotation_;
        rotation_ = glm::normalize(rotation_);
    }

private:
    glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::quat rotation_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

};

#endif // TRANSFORM_H_