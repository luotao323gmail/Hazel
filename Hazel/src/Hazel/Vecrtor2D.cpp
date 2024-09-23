#include "hzpch.h"
#include "Hazel/Vector2D.h"

namespace Hazel {

    // 构造函数
    Vector2D::Vector2D(double x, double y) : x_(x), y_(y) {}

    // 获取 x 和 y 分量
    double Vector2D::getX() const { return x_; }
    double Vector2D::getY() const { return y_; }

    // 重载加法运算符
    Vector2D Vector2D::operator+(const Vector2D& other) const {
        return Vector2D(x_ + other.x_, y_ + other.y_);
    }

    // 重载减法运算符
    Vector2D Vector2D::operator-(const Vector2D& other) const {
        return Vector2D(x_ - other.x_, y_ - other.y_);
    }

    // 重载点乘运算符
    double Vector2D::operator*(const Vector2D& other) const {
        return x_ * other.x_ + y_ * other.y_;
    }

    // 向量的模
    double Vector2D::magnitude() const {
        return std::sqrt(x_ * x_ + y_ * y_);
    }

    // 计算两个向量的夹角
    double Vector2D::angleBetween(const Vector2D& other) const {
        double dotProduct = *this * other;
        double magnitudeA = this->magnitude();
        double magnitudeB = other.magnitude();

        if (magnitudeA == 0.0 || magnitudeB == 0.0) {
            throw std::invalid_argument("向量长度不能为零");
        }

        double cosTheta = dotProduct / (magnitudeA * magnitudeB);
        return std::acos(cosTheta);  // 返回弧度制的角度
    }

    
    std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.x_ << ", " << vec.y_ << ")";
        return os;
    }

} // namespace Hazel
