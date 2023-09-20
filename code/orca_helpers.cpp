/*
File:   orca_helpers.cpp
Author: Taylor Robbins
Date:   09\19\2023
Description:
	** Holds functions that help us deal with orca types and functions
*/

inline oc_mat2x3 ToOcMat(mat4 matrix)
{
	oc_mat2x3 result;
	result.m[0] = matrix.r0c0;
	result.m[1] = matrix.r0c1;
	result.m[2] = matrix.r0c2;
	result.m[3] = matrix.r1c0;
	result.m[4] = matrix.r1c1;
	result.m[5] = matrix.r1c2;
	return result;
}
inline mat4 ToMat4(oc_mat2x3 matrix)
{
	return NewMat4(
		matrix.m[0], matrix.m[1], matrix.m[2], 0,
		matrix.m[3], matrix.m[4], matrix.m[5], 0,
		0,           0,           1,           0,
		0,           0,           0,           1
	);
}

inline oc_vec2 ToOcVec2(v2 vector)
{
	oc_vec2 result;
	result.x = vector.x;
	result.y = vector.y;
	return result;
}
inline v2 ToVec2(oc_vec2 vector)
{
	return NewVec2(vector.x, vector.y);
}

inline oc_rect ToOcRect(rec rectangle)
{
	oc_rect result;
	result.x = rectangle.x;
	result.y = rectangle.y;
	result.w = rectangle.width;
	result.h = rectangle.height;
	return result;
}
inline rec ToRec(oc_rect rectangle)
{
	return NewRec(rectangle.x, rectangle.y, rectangle.w, rectangle.h);
}
