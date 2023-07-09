# Ready, Set, Boole! - An introduction to Boolean Algebra

> _**Summary: Discover the way computers work mathematically.**_


#### [Read this in French](README-fr.md)

## Project Structure
- ReadySetBoole.hpp, ReadySetBoole.cpp
- RPNtree.hpp, RPNtree.cpp

For the project structure, there are two classes called RSB, RPNNode. The first is a class that contains all the methods of the exercises and the second is a class to do the parsing and check the syntax of the propositional formula. 

- exercise.hpp, exercise.cpp
- main.cpp

Then, there are two files exercise.cpp, exercise.hpp to perform the exercises with main.cpp
### Class RSB

[Exercise 00 - Adder](#ex00)<br>
[Exercise 01 - Multiplier](#ex01)<br>
[Exercise 02 - Gray code](#ex02)<br>
[Exercise 03 - Boolean evaluation](#ex03)<br>
[Exercise 04 - Truth table](#ex04)<br>
[Exercise 05 - Negation Normal Form](#ex05)<br>
[Exercise 06 - Conjunctive Normal Form](#ex06)<br>
[Exercise 07 - SAT](#ex07)<br>
[Exercise 08 - Powerset](#ex08)<br>
[Exercise 09 - Set evaluation](#ex09)<br>
[Exercise 10, 11 - Curve, Inverse function](#ex10_11)<br>

---
<a id="ex00"></a>
<table>
<tr><th>Exercise 00 -  Adder</th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : O(1) </tr>
<tr><td>Maximum space complexity : O(1)</tr>
</table>

``` c++
unsigned int RSB::adder(unsigned int a, unsigned int b)
{
        unsigned int carry = 0;

        while (b != 0)
        {
                carry = a & b;
                a = a ^ b;
                b = carry << 1;
        }
        return (a);
};
```
#### How it works:

1. It takes two unsigned integer parameters `a` and `b`.
2. It initializes a `carry` variable to 0 to store the carry.
3. It enters a `while` loop until `b` is equal to 0.
4. On each iteration of the loop, it does the following:
	- It performs a logical **AND** between `a` and `b` to get the carry value.
	- It performs a **XOR** between `a` and `b` to get the sum without carry.
	- It shifts the value of `carry` one position to the left by adding a leading zero.
	- It reassigns the value of `a` to the obtained sum and the value of `b` to carry.
5. Once the value of `b` is equal to 0, the loop ends and the function returns the final value of `a` which is the sum of the two numbers.

#### Complexity:

The complexity of this function is **O(1)**, which means that the execution time doesn't depend on the size of the numbers `a` and `b`. No matter the size of the numbers, the number of iterations of the loop remains constant.

---
<a id="ex01"></a>
<table>
<tr><th>Exercise 01 -  Multiplier</th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : O(1) </tr>
<tr><td>Maximum space complexity : O(1)</tr>
</table>

``` c++
unsigned int RSB::multiplier(unsigned int a, unsigned int b)
{
        unsigned int result = 0;

        while (b != 0)
        {
                // check the least significant bit of b
                if (b & 1)
                        result = adder(result, a);
                a <<= 1;
                b >>= 1;
        }
        return (result);
};
```
#### How it works:

1. It takes two unsigned integer parameters `a` and `b`.
2. It initializes a `result` variable to 0 to store the result of the multiplication.
3. It enters a `while` loop until `b` is equal to 0.
4. On each iteration of the loop, it does the following:
	- It checks the least significant bit of `b` using a logical **AND** with 1.
	- If the bit is equal to 1, it calls the `adder` function to add the value of `a` to `result`.
	- It shifts the value of `a` one position to the left by adding a leading zero.
	- It shifts the value of `b` one position to the right, losing the least significant bit.
5. Once the value of `b` is equal to 0, the loop ends and the function returns the final value of `result`, which is the product of the two numbers.


#### Complexity

The complexity of this function is **O(1)**, because the number of iterations of the `while` loop depends on the number of bits of `b` that remains constant regardless of the size of the numbers `a` and `b`.

---
<a id="ex02"></a>
<table>
<tr><th>Exercise 02 -  Gray code</th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : N/A </tr>
<tr><td>Maximum space complexity : N/A</tr>
</table>

``` c++
unsigned int RSB::grayCode(unsigned int n)
{
        // perform XOR operation between n and n shifted right by 1 bit
        return (n ^ (n >> 1));
};
```

#### How it works:

1. It takes one unsigned integer parameter `n`.
2. It performs a **XOR** between `n` and the result of the `n` shifted right by 1 bit (n >> 1).
3. The result of **XOR** is returned as the Gray code corresponding to `n`.

#### Gray Code

Gray code is a binary number system in which two adjacent numbers differ by only one bit.

Gray code is used in a variety of fields, including electronics, telecommunications, and information theory. It is used to avoid switching errors when switching one binary number to another adjacent binary number.

// une image d'un example du code Gray

---
<a id="ex03"></a>
<table>
<tr><th>Exercise 03 -  Boolean evaluation</th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : O(n) </tr>
<tr><td>Maximum space complexity : N/A</tr>
</table>

``` c++
bool    RSB::evalFormula(const std::string& formula)
{
        std::stack<bool>        eval_stack;

        if (!checkFormula(formula, false, false))
                return false;
        for (char c: formula)
        {
                if (std::isdigit(c))
                {
                        bool value = c == '1';
                        eval_stack.push(value);
                }
                else if (c == '!')
                {
                        bool operand = eval_stack.top();
                        eval_stack.pop();
                        eval_stack.push(!operand);
                }
                else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=')
                {
                        bool operand2 = eval_stack.top();
                        eval_stack.pop();
                        bool operand1 = eval_stack.top();
                        eval_stack.pop();

                        bool result = evalOperator(c, operand1, operand2);
                        eval_stack.push(result);
                }
                else
                        runtimeException("Invalid symbol");
        }
        return eval_stack.top();
};
```
The  `evalOperator` function evaluates an operation between two operands and returns the result. It takes three parameters: the operator (op) and the two operands (operand1, operand2).

The `evalFormula` function evaluates the boolean formula represented by a character string. It uses a stack to evaluate operations and operands.

#### How it works:


1.	It first checks the validity of the formula by calling `checkFormula` function from the `RPNtree.cpp` file with the `formula` parameter. If the formula isn't valid, the function returns `false`. 
2.	Then, it loops through each character in the formula using a `for` loop.
3.	If the character is a digit (0 or 1), it creates a boolean `value` based on the value of the digit and pushes it into the `eval_stack` stack.
4.	If the character is `!`, it retrieves the operand from the top of the stack, pops it off the stack, performs the negation, and pushes the result into the stack.
5.	If the character is one of the operators `&`, `|`, `^`, `>` ou `=`, it retrieves the top two operands from the stack, pops them off the stack, calls the `evalOperator` function with the operator and the operands and pushes the result into the stack. 
6.	If the character isn't none of the valid digits or operators, an "Invalid symbol" exception is thrown.
7.	After looping through all the characters of the formula, the function returns the final result which is at the top of the `eval_stack` stack.

#### Complexity

The complexity of this function depends on the length of the formula (n), so it is **O(n)**.

---
<a id="ex04"></a>
<table>
<tr><th>Exercise 04 - Truth table </th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : O(2^n) </tr>
<tr><td>Maximum space complexity : N/A</tr>
</table>
    
``` c++
void    RSB::printTruthTable(const std::string& formula, bool ordered)
{
        std::vector<std::pair<char, size_t> > variables;
        std::string temp_formula;
        size_t variable_count = 0;
        size_t rows = 0;

        if (!checkFormula(formula, true, false))
                return ;
        variables = getVariables(formula, ordered);
        variable_count = std::max_element(variables.begin(), variables.end(),
                        [](const std::pair<char, size_t>& lhs, const std::pair<char, size_t>& rhs) {
                        return lhs.second < rhs.second;
                        })->second;
        // print column headers
        std::cout << "| ";
        for (size_t i = 0; i <= variable_count - 1; ++i)
                std::cout << variables[i].first << " | ";
        std::cout << "= |\n";
        for (size_t i = 0; i <= variable_count; ++i)
                std::cout << "|---";
        std::cout << "|\n";
        rows = 1 << variable_count;

        for (size_t i = 0; i < rows; ++i)
        {
                std::cout << "| ";
                temp_formula = formula;
                for (int j = variables.size() - 1; j >= 0; --j)
                {
                        size_t value = (i >> (variables[j].second - 1)) & 1;
                        std::cout << value << " | ";
                        std::replace(temp_formula.begin(), temp_formula.end(), variables[j].first, (char)(value + '0'));
                }
                std::cout << evalFormula(temp_formula) << " |\n";
        }
};
```
The `getVariables` function retrieves the variables present in a given boolean formula. it returns a vector of pairs where each pair represents a variable and its order number.

The `printTruthTable` function prints the truth table of a given boolean formula.

#### How it works:

1. It initializes the local variables: `variables` to store the variables present in the formula, `temp_formula` to create a temporary copy of the formula, `variable_count` to determine the number of variables, `rows` for the total number of rows in the truth table.
2. It first checks the validity of the formula by calling the `checkFormula` function with the `formula` parameter. If the formula isn't valid, the function returns.
3. It calls the `getVariables` function to get the variables of the formula, specifying whether they should be sorted or not.
4. It determines the value of `variable_count` using `std::max_element` function on the `variables` vector.
5. it prints the column headers and a separator line.
6. It calculates the total number of rows in the truth table using the binary shift operator (`<<`).
7. It iterates over each row of the truth table.
	- for each row, it prints the variables values by iterating over the variables and using the binary shift operator (`>>`) and the mask (`1`) to extract each bit from the variable value.
	- It replaces the occurrences of the variables in the temporary formula `temp_formula` with the corresponding values (0 or 1) using `std::replace` function.
	- It evaluates the temporary formula by calling `evalFormula` function with the modified formula.
	- It prints the value resulting from the evaluation of the formula.

#### Complexity

The complexity of this function depends on the number of the distinct variables present in the formula because the number of rows in the truth table is  $2^n$, where `n` is the number of distinct variables. Therefore, the complexity of this function is $O(2^n)$.

---
<a id="ex05"></a>
<table>
<tr><th>Exercise 05 - Negation Normal Form </th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : N/A </tr>
<tr><td>Maximum space complexity : N/A</tr>
</table>

``` c++  
const std::string       RSB::negationNormalForm(const std::string& formula)
{
        std::stack<std::string> stack;
        std::string temp, temp2, temp_formula;

        if (!checkFormula(formula, true, false))
                return formula;
        temp_formula = rewriteFormula(formula);
        for (char c : temp_formula)
        {
                if (isalpha(c))
                        stack.push(std::string(1, c));
                else if (c == '!')
                {
                        if (!stack.empty())
                        {
                                temp = stack.top(); stack.pop();
                                temp2 = applyNegation(temp);
                                stack.push(temp2);
                        }
                }
                else if (c == '&' || c == '|')
                {
                        temp = stack.top(); stack.pop();
                        temp2 = stack.top(); stack.pop();
                        stack.push(temp2 + temp + c);
                }
                else
                        runtimeException("Invalid symbol", std::string(1, c));
        }
        return stack.top();
};
```
The `applyNegation` is used to apply the negation to a variable or to a subformula in a boolean formula.

The `rewriteFormula` function is used to simplify a boolean formula using simplification rules.
The `negationNormalForm` is used to convert a boolean formula to Negation Normal Form (NNF) using `applyNegation` and `rewriteFormula` functions.

#### How it works:

1. It uses a stack to store the intermediate subformulas.
2. It simplifies the original formula by calling the `rewriteFormula` function with the formula.
3. It loops through each character of the simplified formula using a `for` loop.
4. If the character is a letter (a variable), it simply pushes it into the stack.
5. If the character is `!`, it applies the negation to the last subformula on the stack using `applyNegation` function and then pushes the resulting subformula into the stack.
6. If the character is `&` or `|`, it retrieves the last two subformulas from the stack, pops them off the stack, then pushes a new resulting subformula into the stack using the character as an operator.
7. If the character isn't a `!`, `&` or `|` letter, an "Invalid symbol" exception is thrown.
8. After all the characters in the formula have been processed, the function returns the final subformula which is at the top of the stack.

---
<a id="ex06"></a>
<table>
<tr><th>Exercise 06 - Conjunctive Normal Form </th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : N/A </tr>
<tr><td>Maximum space complexity : N/A</tr>
</table>

``` c++
const std::string       RSB::conjunctiveNormalForm(const std::string& formula)
{
        std::unique_ptr<RPNNode>        cnf;
        std::string temp_formula;
        std::string result;

        if (!checkFormula(formula, true, false))
                return formula;
        temp_formula = negationNormalForm(formula);
        temp_formula = rearrangeOnlyAndOr(temp_formula);

        cnf = buildTree(temp_formula);
        if (checkAndBeforeOr(temp_formula))
                cnf = applyDistributiveLaw(cnf);
        cnf = rearrangeConjunctions(cnf);
        result = preorder(cnf);

        return result;
};
```
The `rearrangeOnlyAndOr` function checks if the formula contains only conjunction(`&`) or disjunction(`|`) operators. If it so, it rearranges the modified formula by moving all the operators to the end of the formula, otherwise, it returns the origin formula. 

The `checkAndBeforeOr` function checks if the conjunction operator appears before the disjunction operator in the formula. If so, it returns `true`, otherwise it returns `false`.

The `applyDistributiveLaw` and `rearrangeConjunctions` functions are used to manipulate a tree structure representing a formula in Reverse Polish Notation (RPN). `applyDistributiveLaw` applies the distributive law to the formula tree. `rearrangeConjunctions` allows to rearrange the conjunctions in the formula tree.

The `conjunctiveNormalForm` function is used to convert a boolean formula to Conjunctive Normal From (CNF).

#### How it works:

1. It first checks the validity of the formula by calling the `checkFormula` function with the formula. If the formula is not valid, the function returns the origin formula.
2. It applies the Negation Normal From (NNF) to the formula by calling the `negationNormalForm` function.
3. It rearranges the conjunction and disjunction operators by calling the `rearrangeOnlyAndOr` function.
4. It checks if the conjunction operator appears before the disjunction operator by calling the `checkAndBeforeOr` function. If so, the function applies the distributive law by calling the `applyDistributiveLaw` function.
5. It rearranges the conjunctions in the syntax tree by calling the `rearrangeConjunctions` function.
6. It retrieves the resulting formula by traversing the syntax tree in prefix order using the `preorder` function.
7. It returns the resulting formula.

---
<a id="ex07"></a>
<table>
<tr><th>Exercise 07 - SAT </th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : O(2^n) </tr>
<tr><td>Maximum space complexity : N/A</tr>
</table>


``` c++
bool    RSB::sat(const std::string& formula)
{
        std::vector<std::pair<char, size_t> > variables;
        std::string temp_formula = formula;
        size_t variable_count = 0;
        size_t rows = 0;

        if (!checkFormula(formula, true, false))
                return false;
        variables = getVariables(formula, false);
        variable_count = std::max_element(variables.begin(), variables.end(),
                        [](const std::pair<char, size_t>& lhs, const std::pair<char, size_t>& rhs) {
                        return lhs.second < rhs.second;
                        })->second;
        rows = 1 << variable_count;
        for (size_t i = 0; i < rows; ++i)
        {
                temp_formula = formula;
                for (const auto& variable : variables)
                {
                        size_t m_value = (i >> (variable.second - 1)) & 1;
                        std::replace(temp_formula.begin(), temp_formula.end(), variable.first, (char)(m_value + '0'));
                }
                if (evalFormula(temp_formula))
                        return true;
        }
        return false;
};
```

The `getVariables` function retrieves the variables present in a given boolean formula. it returns a vector of pairs where each pair represents a variable and its order number.

The `evalFormula` function evaluates the boolean formula represented by a character string. it uses a stack to evaluate operators and operands.

The `sat` function is used to check if a given logic formula is satisfiable, which means if there exists an assignment of values to the variables of the formula that makes the formula true.

#### How it works:

1. It starts by checking if the formula is valid by calling the `checkFormula` function, if the formula isn't valid, it returns `false` because it can't be satisfiable.
2. It uses the `getVariables` function to get the distinct variables present in the formula.
3. It determines the number of rows needed to generate the possible combinations of values for the variables.
4. It iterates through each possible row of values for the variables.
	- for each row, it creates a temporary copy of the initial formula.
	- for each row, it retrieves the values of the variables by iterating over the variables and using the binary shift operator (`>>`) and the mask (`1`) to extract each bit from the value of the variable.
	- It replaces the occurrences of the variables in the temporary formula `temp_formula` with the corresponding values (0 or 1) using the `std::replace` function.
	- It evaluates the temporary formula by calling the `evalFormula` function with the modified formula.
	- If the temporary formula is evaluated as true, it means that the initial formula is satisfiable, and the function returns `true`.
5. If no combination of values satisfies the formula, the function returns `false`.

#### Complexity

The complexity of this function depends on the number of variables in the formula. the total number of rows generated is 2^n, where `n` is the number of distinct variables. For each row, the function performs a replace operation in the temporary formula and evaluates the modified formula by calling the `evalFormula` function. Therefore, the complexity of this function is **$O(2^n)$**, where `n` is the number of distinct variables.

---
<a id="ex08"></a>
<table>
<tr><th>Exercise 08 - Powerset </th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : N/A </tr>
<tr><td>Maximum space complexity : O(2^n)</tr>
</table>

``` c++
static void     generatePowerset(const t_set& set, t_set& current_set, int index, t_powerset& powerset)
{
        powerset.push_back(current_set);
        for (size_t i = index; i < set.size(); ++i)
        {
                current_set.push_back(set[i]);
                generatePowerset(set, current_set, i + 1, powerset);
                current_set.pop_back();
        }
};
t_powerset      RSB::powerset(t_set& set)
{
        t_powerset      powerset;
        t_set           current_set;

        generatePowerset(set, current_set, 0, powerset);
        return powerset;
};
```

The `generatePowerset` and `powerset` functions are used to generate the powerset (set of subsets) from a given set.

#### How it works:

1. `generatePowerset` is a recursive function that takes as input a `set` set, a `current_set` set (which contains the current elements of the subset being generated), an `index` (to tract the current position during generation), a `powerset` (which will contain all generated subsets).
2. It starts by adding the `current_set` to the powerset, because it is a valid subset.
3. Then, it iterates through the elements of the set `set` starting at the given index.
4. For each element from the index, it adds it to the set `current_set`, then it recursively calls the `generatePowerset` function by incrementing the index by 1. This generates the subsets containing this element.
5. After the recursive call, it removes the last element added to `current_set` using the `pop_back` function. This makes it possible to return to the previous state and to generate the subsets without this element.
6. The function terminates when all the elements of the `set` set have been traversed.
7. The final powerset is returned.

#### Complexity

The complexity of this function is  **$O(2^n)$**, where `n` is the size of the given set. This is because the powerset contains 2^n distinct subsets, and each subset is generated once.

---
<a id="ex09"></a>
<table>
<tr><th>Exercise 09 - Set evaluation </th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : N/A </tr>
<tr><td>Maximum space complexity : N/A</tr>
</table>

``` c++
t_set   RSB::evalSet(const std::string& formula, const t_powerset& sets)
{
        std::stack<t_set>       stack;
        std::vector<char>       variables;
        std::string                     temp_formula;
        t_set                           universal_set;
        size_t                          variable_count = 0;

        for (const t_set& set : sets)
        {
                for (int element : set)
                {
                        if (std::find(universal_set.begin(), universal_set.end(), element) == universal_set.end())
                                universal_set.push_back(element);
                }
        }

        temp_formula = negationNormalForm(formula);
        for (char c : temp_formula)
        {
                if (isalpha(c))
                {
                        bool exist = false;
                        for (size_t j = 0; j < variables.size(); ++j)
                        {
                                if (variables[j] == c)
                                {
                                        exist = true;
                                        stack.push(sets[j]);
                                        break;
                                }
                        }
                        if (!exist)
                        {
                                stack.push(sets[variable_count]);
                                variables.emplace_back(c);
                                variable_count++;
                        }
                }
                else if (c == '!') // Negation
                {
                        t_set operand = stack.top(); stack.pop();
                        t_set result;

                        for (int element : universal_set)
                        {
                                if (std::find(operand.begin(), operand.end(), element) == operand.end())
                                        result.push_back(element);
                        }
                        stack.push(result);
                }
                else if (c == '&' || c == '|' || c == '^' || c == '=' || c == '>')
                {
                        t_set operand2 = stack.top(); stack.pop();
                        t_set operand1 = stack.top(); stack.pop();
                        t_set result;
                        if (c == '&') // Intersection
                        {
                                std::unordered_map<int, bool> set1_elements;
                                for (int element : operand1)
                                        set1_elements[element] = true;
                                for (int element : operand2)
                                {
                                        if (set1_elements[element])
                                                result.push_back(element);
                                }
                        }
                        else if (c == '|') // Union
                        {
                                result = operand1;
                                for (int element : operand2)
                                {
                                        if (std::find(result.begin(), result.end(), element) == result.end())
                                                result.push_back(element);
                                }
                        }
                        else if (c == '^') // Symmetric difference
                        {
                                std::unordered_map<int, bool> set1_elements;
                                std::unordered_map<int, bool> set2_elements;

                                for (int element : operand1)
                                        set1_elements[element] = true;
                                for (int element : operand2)
                                {
                                        if (!set1_elements[element])
                                                result.push_back(element);
                                }
                                for (int element : operand2)
                                        set2_elements[element] = true;
                                for (int element : operand1)
                                {
                                        if (!set2_elements[element])
                                                result.push_back(element);
                                }
                        }
                        stack.push(result);
                }
        }
        return stack.top();
};
```
The `evalSet` function is used to evaluate a logic formula with sets.

#### How it works:

1. It creates a stack to store the temporary sets generated while evaluating the formula.
2. It creates a `variables` vector to store the distinct variables present in the formula.
3. It creates a universal set `universal_set` which contains all the elements present in the set `powerset`. It is necessary for handling the negation operation.
4. It converts the formula to Negation Normal Form (NNF) by calling the `negationNormalForm` function.
5. It iterates over each character of the converted formula:
	- If the character is a letter (variable), it checks if the variable has already been encountered. If so, it retrieves the corresponding set in the `sets` powerset, and pushes it into the stack. Otherwise, it creates a new variable, retrieves the corresponding set from the `sets` powerset and pushes it into the stack, while adding the variable to the `variables` vector.
	- If the character is a negation operation `!`, it retrieves the set which is located on top of the stack, performs the negation using the universal set, and pushes the result into the stack.
	- If the character is an operation (`&`, `|`, `^`, `=`, `>`), it retrieves the top two sets from the stack, performs the corresponding operation, and pushes the result into the stack.
6. At the end of the iteration, the resulting set is located on top of the stack and it is returned.

---
<a id="ex10_11"></a>
<table>
<tr><th>Exercise 10, 11 - Curve, Inverse function </th></tr>
<tr><td>Allowed mathematical functions : None </tr>
<tr><td>Maximum time complexity : N/A </tr>
<tr><td>Maximum space complexity : N/A</tr>
</table>

``` c++
#define MAX_VALUE ((1ULL << 32) - 1)

double  RSB::map(unsigned short x, unsigned short y)
{
        // combine x and y into a 64-bit value
        unsigned long long value = (static_cast<unsigned long long>(x) << 16) | y;
        // map the value to the range [0; 1]
        double result = static_cast<double>(value) / MAX_VALUE;

        return result;
};

t_vec2s RSB::reverseMap(double n)
{
        // reverse normalize the value
        unsigned long long value = static_cast<unsigned long long>(n * MAX_VALUE);
        // extract the x coordinate
        unsigned short x = static_cast<unsigned short>(value >> 16);
        // extract the y coordinate
        unsigned short y = static_cast<unsigned short>(value & 0xFFFF);

        t_vec2s result;
        result.x = x;
        result.y = y;

        return result;
};
```

The `map` function is used to map two unsigned integer values (`x` and `y`) into a real value in the range [0, 1].

1. It combines the values `x` and `y` into a 64-bit integer value using a bit shift and a **OR** logic.
2. Then, it converts this integer value into a double and divides it by the constant `MAX_VALUE` to get a real value in the range [0, 1].
3. The real value is returned.

The `reverseMap` function performs the reverse operation of the `map` function.

1. It takes as input a real value in the range [0, 1]/
2. The value first is multiplied by the constant `MAX_VALUE` to get a 64-bit integer value.
3. Then, this integer value is used to extract the `x` and `y` values using the bit shift and masking operations.
4. The `x` and `y` values are stored in a `t_vec2s` structure and returned.
