#pragma once

typedef enum {
    Left = 1 << 0,
    Right = 1 << 1,
    HorizontalCenter = 1 << 2,
    Top = 1 << 3,
    Bottom = 1 << 4,
    VerticalCenter = 1 << 5,

    TopLeft = Top | Left,
    TopCenter = Top | HorizontalCenter,
    TopRight = Top | Right,

    CenterLeft = VerticalCenter | Left,
    Center = VerticalCenter | HorizontalCenter,
    CenterRight = VerticalCenter | Right,

    BottomLeft = Bottom | Left,
    BottomCenter = Bottom | HorizontalCenter,
    BottomRight = Bottom | Right,
} TextAlignment;

