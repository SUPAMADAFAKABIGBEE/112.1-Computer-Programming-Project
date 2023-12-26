//
//  Bar.cpp
//  Project
//
//  Created by Richard on 2023/12/24.
//

#include "Bar.h"

int Bar::totalBar = 0;

void Bar::changeAlpha()
{
	setAlpha(255 - 10 * (Bar::totalBar - order) > 0 ? 255 - 10 * (Bar::totalBar - order) : 0);
}
