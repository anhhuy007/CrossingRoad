#include "Colors.h"

int COLOR::GetColor(
	COLOR foregroundColor,
	COLOR backgroundColor
) {
	return (int)foregroundColor | (int)backgroundColor << 4;
}