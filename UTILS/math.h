/*
 * math.h
 *
 *  Created on: Dec 27, 2019
 *      Author:
 */

#ifndef UTILS_MATH_H_
#define UTILS_MATH_H_

#define SET_BIT(REG,BIT) 	REG |= (1<<BIT)
#define CLEAR_BIT(REG,BIT)	REG &= ~(1<<BIT)
#define TOGGLE_BIT(REG,BIT)	REG ^= (1<<BIT)
#define GET_BIT_VALUE(REG,BIT) ((REG & (1<<BIT)) >> BIT)  //check bit replaced by if

#endif /* UTILS_MATH_H_ */


