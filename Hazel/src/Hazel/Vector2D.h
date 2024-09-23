#pragma once
#ifndef HAZEL_VECTOR2D_H
#define HAZEL_VECTOR2D_H

#include <iostream>
#include <cmath>
#include <stdexcept>

// ʹ�� Hazel �����ռ�
namespace Hazel {

    class HAZEL_API Vector2D {
    public:
        // ���캯��
        Vector2D(double x = 0.0, double y = 0.0);

        // ��ȡ������ x �� y ����
        double getX() const;
        double getY() const;

        // ���ؼӷ������
        Vector2D operator+(const Vector2D& other) const;

        // ���ؼ��������
        Vector2D operator-(const Vector2D& other) const;

        // ���ص�������
        double operator*(const Vector2D& other) const;

        // ������ģ�����ȣ�
        double magnitude() const;

        // �������������ļнǣ����ȣ�
        double angleBetween(const Vector2D& other) const;

        // �����������Ԫ����
        HAZEL_API friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);

    
        double x_, y_;  // ������ x �� y ����
    };

} // namespace Hazel

#endif // HAZEL_VECTOR2D_H
