/*  Andrew Borgan  0945189
 *  Monday, October 17th, 2016
 */

#ifndef __POSTSCRIPT_H__
#define __POSTSCRIPT_H__

/*  runPostScript
 *
 *  This function loops through the passed in postfix and calls other functions
 *  depending on the character at the current position.  It then prints out the total
 *  of the postfix calculation.
 *
 *  In: N/A
 *
 *  Out: prints total to the screen
 *
 *  Post: N/A
 *
 *  Error: will produce an error message if one of the first two characters is not a digit.
 *  (invalid postfix)
 */
void runPostScript();

/*  push
 *
 *  This function puts the next element on top of the stack for use later.
 *
 *  In: next (item to be pushed into stack)
 *
 *  Out: N/A
 *
 *  Post: New item in stack
 *
 *  Error: do not attempt to push values that are not doubles or errors may occur.
 */
void push(double next);

/*  pop
 *
 *  This function retrieves the top item from the stack for use and decreases the stack by one.
 *
 *  In: N/A
 *
 *  Out: returns top item from stack
 *
 *  Post: stack is decreased
 *
 *  Error: will produce an error message if you try to pop an empty stack
 */
double pop();

/*  calculate
 *
 *  This function takes two values performs a calculation depending on the operator passed in (+ is addition, - is subtraction,
 *  * is multiplication, / is division)
 *
 *  In: first, second, operator, performs operation in the form (first (operator) second).
 *
 *  Out: returns the result of the operation
 *
 *  Post: N/A
 *
 *  Error:  Will produce an error message if you attempt to divide by 0
 */
double calculate(double first, double second, char operator);

#endif
