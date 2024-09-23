#pragma once
#ifndef HAZEL_VECTOR2D_H
#define HAZEL_VECTOR2D_H

#include <iostream>
#include <cmath>
#include <stdexcept>

// 使用 Hazel 命名空间
namespace Hazel {

    class HAZEL_API Vector2D {
    public:
        // 构造函数
        Vector2D(double x = 0.0, double y = 0.0);

        // 获取向量的 x 和 y 分量
        double getX() const;
        double getY() const;

        // 重载加法运算符
        Vector2D operator+(const Vector2D& other) const;

        // 重载减法运算符
        Vector2D operator-(const Vector2D& other) const;

        // 重载点乘运算符
        double operator*(const Vector2D& other) const;

        // 向量的模（长度）
        double magnitude() const;

        // 计算两个向量的夹角（弧度）
        double angleBetween(const Vector2D& other) const;

        // 输出向量的友元函数
        HAZEL_API friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);

    
        double x_, y_;  // 向量的 x 和 y 分量
    };

} // namespace Hazel

#endif // HAZEL_VECTOR2D_H
