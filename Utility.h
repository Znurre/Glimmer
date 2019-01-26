#ifndef UTILITY_H
#define UTILITY_H

template<typename T>
T lerp(T start, T end, float value)
{
	return start + (end - start) * value;
}

#endif // UTILITY_H
