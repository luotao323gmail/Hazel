#include "hzpch.h"
#include "Hazel/Vector2D.h"

namespace Hazel {

    // ���캯��
    Vector2D::Vector2D(double x, double y) : x_(x), y_(y) {}

    // ��ȡ x �� y ����
    double Vector2D::getX() const { return x_; }
    double Vector2D::getY() const { return y_; }

    // ���ؼӷ������
    Vector2D Vector2D::operator+(const Vector2D& other) const {
        return Vector2D(x_ + other.x_, y_ + other.y_);
    }

    // ���ؼ��������
    Vector2D Vector2D::operator-(const Vector2D& other) const {
        return Vector2D(x_ - other.x_, y_ - other.y_);
    }

    // ���ص�������
    double Vector2D::operator*(const Vector2D& other) const {
        return x_ * other.x_ + y_ * other.y_;
    }

    // ������ģ
    double Vector2D::magnitude() const {
        return std::sqrt(x_ * x_ + y_ * y_);
    }

    // �������������ļн�
    double Vector2D::angleBetween(const Vector2D& other) const {
        double dotProduct = *this * other;
        double magnitudeA = this->magnitude();
        double magnitudeB = other.magnitude();

        if (magnitudeA == 0.0 || magnitudeB == 0.0) {
            throw std::invalid_argument("�������Ȳ���Ϊ��");
        }

        double cosTheta = dotProduct / (magnitudeA * magnitudeB);
        return std::acos(cosTheta);  // ���ػ����ƵĽǶ�
    }

    
    std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.x_ << ", " << vec.y_ << ")";
        return os;
    }

} // namespace Hazel
