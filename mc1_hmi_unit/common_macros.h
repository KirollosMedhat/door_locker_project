/*
 * common_macros.h
 *
 *  Created on: Jul 19, 2021
 *      Author: Kirollos
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_


#define BIT_IS_CLEAR(REG,PIN) (! (REG&(1<<PIN)) )
#define BIT_IS_SET(REG,PIN) ( REG&(1<<PIN) )
#define SET_BIT(REG,PIN) (REG=REG|(1<<PIN))
#define CLEAR_BIT(REG,PIN) (REG=REG&(~(1<<PIN)))




#endif /* COMMON_MACROS_H_ */
