#### [Read this in English](README.md)

## La Structure du projet
- ReadySetBoole.hpp, ReadySetBoole.cpp
- RPNtree.hpp, RPNtree.cpp

Pour la structure du projet, il exist deux classes appelées RSB, RPNNode. La première est une classe qui contient toutes les méthodes des exercices et la seconde est une classe pour faire le parsing et vérifier la syntax de la formule propositionnelle.

- exercise.hpp, exercise.cpp
- main.cpp

Ensuite, Il exist deux fichiers exercise.cpp, exercise.hpp pour effectuer les exercices avec main.cpp

### Classe RSB

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
#### Comment elle fonctionne:

1. Elle prend deux parametères entiers non signés `a` et `b`.
2. Elle initialise une variable `carry` à 0 pour stocker la retenue.
3. Elle entre dans une boucle `while` tant que `b` n'est pas égal à 0.
4. À chaque itération de la boucle, elle effectue les opérations suivantes:
	- Elle effectue un **ET** logique entre `a` et `b` pour obtenir la valeur de la retenue.
	- Elle effectue un **XOR**  entre `a` et `b` pour obtenir la somme sans retenue.
	- Elle décale la valeur de `carry` d'une position vers la gauche en ajoutant un zéro à droite.
	- Elle réassigne la valuer de `a` à la somme obtenue et la valeur de `b` à `carry`.
5. Une fois la valeur de `b` est égal à 0, la boucle se termine et la fonction returne la valeur finale de `a` qui est la somme des deux nombres.

#### Complexité:

La complexité de cette fonction est **O(1)**, ce qui signifie que le temps d'execution ne dépend pas de la taille des nombres `a` et `b`. Peu importe la taille des nombres, le nombre d'itérations de la boucle reste constant.

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
#### Comment elle fonctionne:

1. Elle prend deux parametères entiers non signés `a` et `b`.
2. Elle initialise une variable `result` à 0 pour stocker le résultat de la multiplication.
3. Elle entre dans la boucle `while` tant que `b` n'est pas égal à 0.
4. À chaque itération de la boucle, elle effectue les opérations suivantes:
	- Elle vérifie le bit de poids faible de `b` en utilisant un **ET** logique avec 1.
	- Si le bit est égal à 1, elle appelle la fonction `adder` pour ajouter la valeur de `a` à `result`.
	- Elle décale la valeur de `a` d'une position vers la gauche en ajoutant un zéro à droite.
	- Elle décale la valeur de `b` d'une position vers la droite en perdant le bit de poids faible.
5. Une fois la valeur de `b` est égal à 0, la boucle se termine et la fonction returne la valeur finale de `result`, qui est le produit des deux nombres.

#### Complexité

La complexité de cette fonction est **O(1)**, car le nombre d'itérations de la boucle `while` dépend du nombre de bits de `b` qui reste constant indépendamment de la taille des nombres `a` et `b`.

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

#### Comment elle fonctionne:

1. Elle prend un parametère entire non signé `n`.
2. Elle effectue un **XOR** entre `n` et le résultat du décalage de `n` d'un bit vers la droite (n >> 1).
3. Le résultat du **XOR** est renvoyé comme le code Gray correspondant à `n`.

#### Code Gray

Le code Gray est un système de numération binaire dans lequel deux nombres adjacents ne diffèrent que d'un seul bit.

Le code Gray est utilisé dans divers domaines, notamment en électroniques, en télécommunications et en théorie de l'information. Il est utilisé pour éviter les erreurs de commutation lors du passage d'un nombre binaire à un autre nombre binaire adjacent.
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
La fonction `evalOperator` évalue une opération entre deux opérandes et renvoye le résultat. elle prend trois parametères: l'opérateur (op) et les deux opérandes (oprand1, oprand2).

La fonction `evalFormula` évalue la formule booléenne répresentée par une chaîne de caractères. elle utilise une pile(stack) pour évaluer les opérations et les opérandes.

#### Comment elle fonctionne:

1.	Elle vérifie d'abord la validité de la formule en appelant la fonction `checkFormula` du fichier `RPNtree.cpp` avec le parametère `formula`. Si la formule n'est pas valide, la foction renvoye `false`.
2.	Ensuite, elle parcourt chaque caractère de la formule en utilisant une boucle `for`.
3.	Si le caractère est un chiffre (0 ou 1), elle crée un booléen `value` en fonction de la valeur du chiffre et le pousse dans la pile `eval_stack`.
4.	Si le caractère est `!`, elle récupère l'opérande en haut de la pile, l'enlève de la pile, effectue la négation et pousse le résultat dans la pile.
5.	Si le caractère est l'un des opératieurs `&`, `|`, `^`, `>` ou `=`, elle récupère les deux opérandes supérieurs de la pile, les enlève de la pile, appelle la fonction `evalOperator` avec l'opérateur et les opérandes et pousse le résultat dans la pile.
6.	Si le caractère n'est aucun des chiffres ni des opérateurs valides, une exception "Invalid symbol" est lancée.
7.	Après avoir parcouru tous les caractère de la formule, la fonction revoie le résultat final qui se trouve en haut de la pile `eval_stack`.

#### Complexité

La complexité de cette fonction dépend de la longeur de la formule (n), donc elle est **O(n)**.


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
La fonction `getVariables` récupère les variables présentes dans une formule booléenne donnée. elle renvoie un vecteur de paires où chaque paire représente une variable et son numéro d'ordre.

La fonction `printTruthTable` imprime la table de vérité d'une formule booléenne donnée.

#### Comment elle fonctionne:

1. Elle initialise les variables locales: `variables` pour stocker les variables présentes dans la formule, `temp_formula` pour créer une copie temporaire de la formule, `variable_count` pour déterminer le nombre de variables, `rows` pour le nombre total de lignes dans la table de vérité.
2. Elle vérifie d'abord la validité de la formule en appelant la fonction `checkFormula` avec le parametère `formula`. Si la formule n'est pas valide, la fonction renvoye.
3. Elle appelle la fonction `getVariables` pour obtenir les variables de la formule, en spécifiant si elles doivent être triées ou non.
4. Elle détermine la valeur de `variable_count` en utilisant la fonction `std::max_element` sur le vecteur `variables`.
5. Elle imprime les en-têtes de colonnes et une ligne de séparation.
6. Elle calcule le nombre total de lignes dans la table de vérité en utilisant l'opérateur de décalage binaire (`<<`).
7. Elle itère sur chaque ligne de la table de vérité.
	- pour chaque ligne, elle imprime les valeurs des variables en parcourant les variables et en utilisant l'opération de décalage binaire (`>>`) et le masque (`1`) pour extraire chaque bit de la valeur de la variable.
	- Elle remplace les occurances des variables dans la formule temporaire `temp_formula` par les valeurs correspondantes (0 ou 1) à l'aide de la fonction `std::replace`.
	- Elle évalue la formule temporaire en appelant la fonction `evalFormula` avec la formule modifée.
	- Elle imprime la valeur résultante de l'évaluation de la formule.

#### Complexité

La complexité de cette fonction dépend du nombre de variables distinctes présentes dans la formule, car le nombre de lignes dans la table de vérité est $2^n$, où `n` est le nombre de variables distinctes. Par conséquent, la complexité de cette fonction est $O(2^n)$.


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
La fonction `applyNegation` est utilisé pour appliquer la négation à une variable ou à une sous-formule dans une formule booléenne.

La fonction `rewriteFormula` est utilisé pour simplifier une formule booléenne en utilisant des règles de simplication.

La fonction `negationNornalForm` est utilisé pour convertir une formule booléenne en Forme Normale de Négation (NNF) en utilisant les fonctions `applyNegation` et `rewriteFormula`.

#### Comment elle fonctionne:

1. Elle utilise une pile `stack` pour stocker les sous-formules intermédiaires.
2. Elle simplifie la formule initiale en appelant la fonction `rewriteFormula` avec la formule.
3. Elle parcourt chaque caractère de la formule simplifiée en utilisant une boucle `for`.
4. Si le caractère est une lettre (une variable), elle l'ajoute simplement à la pile.
5. Si le caractère est `!`, elle applique la négation à la dernière sous-formule de la pile en utilisant la fonction `applyNegation` puis pousse la sous-formule résultante à la pile.
6. Si le caractère est `&` ou `|`, elle récupère les deux dernières sous-formules de la pile, les supprime de la pile, puis pousse une nouvelle sous-formule résultante à la pile en utilisant le caractère comme opérateur.
7. Si le caractère n'est pas une lettre `!`, `&` ou `|`, une exception "Invalid symbol" est levée.
8. Une fois que tous les caractères de la formule ont été traités, la fonction renvoie la sous-formule finale, qui se trouve en haut de la pile `stack`. 

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
La fonction `rearrangeOnlyAndOr`  vérifie si la formule contient uniquement des opérateurs de conjonction(`&`) ou disjonction(`|`). Si c'est le cas, elle réarrange la formule modifié en déplaçant tous les opérateurs à la fin de la formule, sinon elle renvoie la formule d'origine.

La fonction `checkAndBeforeOr` vérifie si l'opération de conjonction apparaît avant l'opération de disjonction dans la formule. Si c'est le cas, elle renvoie `true`, sinon elle renovie `false`.

Les fonctions `applyDistributiveLaw` et `rearrangeConjunctions` sont utilisées pour manipuler une structure d'arbre représentante une formule en notation polonaise inversée (RPN). `applyDistributiveLaw`  applique la loi distributive à l'arbre de formule. `rearrangeConjunctions` permet de réarranger les conjonctions dans l'arbre de formule.

La fonction `conjunctiveNormalForm` est utilisé pour convertir une formule booléenne en Form Normal Conjonctive (CNF).

#### Comment elle fonctionne:

1. Elle vérifie d'abord la validité de la formule en appelant la fonction `checkFormula` avec la formule. Si la formule n'est pas valide, la fonction renvoie la formule d'origine.
2. Elle applique la négation normale (NNF) à la formule en appelant la fonction `negationNormalForm`.
3. Elle réarrange les opérations de conjonctions et de disjonctions en appelant la fonction `rearrangeOnlyAndOr`.
4. Elle vérifie si l'opération de conjonction apparaît avant l'opération de disjonction en appelant la fonction `checkAndBeforeOr`. Si c'est le cas, la fonction applique la loi distributive en appelant la fonction `applyDistributiveLaw`.
5. Elle réarrange les conjonctions dans l'arbre syntaxique en appelant la fonction `rearrangeConjunctions`.
6. Elle récupère la formule résultante en parcourant l'arbre syntaxique dans l'ordre préfixe à l'aide de la fonction `preorder`.
7. Elle renvoie la formule résultante.

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
La fonction `getVariables` récupère les variables présentes dans une formule booléenne donnée. elle renvoie un vecteur de paires où chaque paire représente une variable et son numéro d'ordre.

La fonction `evalFormula` évalue la formule booléenne répresentée par une chaîne de caractères. elle utilise une pile pour évaluer les opérations et les opérandes.

La fonction `sat` est utilisé pour vérifier si une formule logique donnée est satisfiable, c'est-à-dire s'il existe une affectation de valeurs aux variables de la formule qui rend la formule vraie.

#### Comment elle fonctionne:

1. Elle commence par vérifier si la formule est valide en appelant la fonction `checkFormula`, si la formule n'est pas valide, elle renvoie `false` car elle ne peut pas être satisfiable.
2. Elle utilise la fonction `getVariables` pour obtenir les variables distinctes présentes dans la formule.
3. Elle détermine le nombre de lignes nécessaires pour générer les combinaisons possible de valeurs pour les variables. 
4. Elle itère pour chaque ligne possible de valeurs pour les variables.
	- pour chaque ligne, elle crée une copie temporaire de la formule initiale.
	- pour chaque ligne, elle récupère les valeurs des variables en parcourant les variables et en utilisant l'opération de décalage binaire (`>>`) et le masque (`1`) pour extraire chaque bit de la valeur de la variable.
	- Elle remplace les occurances des variables dans la formule temporaire `temp_formula` par les valeurs correspondantes (0 ou 1) à l'aide de la fonction `std::replace`.
	- Elle évalue la formule temporaire en appelant la fonction `evalFormula` avec la formule modifée.
	- Si la formule temporaire est évaluée comme vraie, cela signifie que la formule initiale est satisfiable, et la fonction renvoie `true`.
5. Si aucune combinaison de valeurs ne satisfait la formule, la fonction renvoie `false`.

#### Complexité

La complexité de cette fonction dépend du nombre de variables dans la formule. Le nombre total de lignes générées est de 2^n, où `n` est le nombre de variables distinctes. Pour chaque ligne, la fonction effectue une opération de remplacement dans la formule temporaire et évalue la formule modifiée en appelant la fonction `evaleFormule`. Par conséquent, la complexité de cette fonction est de l'ordre de **$O(2^n)$**, où `n` est le nombre de variables distinctes. 


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
Les fonctions `generatePowerset` et `powerset` sont utilisées pour générer le powerset (ensemble des sous-ensembles) d'un ensemble donné.

#### Comment elle fonctionne:
1. `generatePowerset` est une fonction récursive qui prend en entrée un ensemble `set`, un ensemble `current_set`(qui contient les éléments actuels du sous-ensemble en cours de génération), un `index` (pour suivre la position actuelle lors de la génération), un`powerset` (qui contiendra tous les sous-ensembles générés).
2. Elle commence par ajouter l'ensemble `current_set` au powerset, car il s'agit d'un sous-ensemble valide.
3. Ensuite, elle parcourt les éléments de l'ensemble `set` à partir de l'index donné.
4. Pour chaque élément à partir de l'index, elle l'ajoute à l'ensemble `current_set`, puis elle appelle récursivement la fonction `generatePowerset` en incrémentant l'index de 1. cela permet de générer les sous-ensmeble contenant cet élément.
5. Après l'appel récursif, elle supprime le dernier élément ajouté à `current_set` en utilisant la fonction `pop_back`. Cela permet de revenir à l'état précédent et de générer les sous-ensembles sans cet élément.
6. La fonction se termine lorsque tous les éléments de l'ensemble `set` ont été parcourus.
7. Le powerset final est renvoyé.

#### Complexité

La complexité de cette fonction est de l'ordre de **$O(2^n)$**, où `n` est la taille de l'ensemble donné. Cela est dû au fait que le powerset contient 2^n sous-ensembles distincts, et chaque sous-ensemble est généré une fois.

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
La fonction `evalSet` est utilisée pour évaluer une formule logique avec des ensembles.

#### Comment elle fonctionne:

1. Elle crée une pile pour stocker les ensembles temporaires générés lors de l'évaluation de la formule.
2. Elle crée un vecteur `variables` pour stocker les variables distinctes présentes dans la formule.
3. Elle crée un ensemble universel `universal_set` qui contient tous les éléments présents dans l'ensemble du powerset. C'est nécessaire pour la manipulation de l'opération de négation.
4. Elle convertit la formule en Forme Normale de Négation (NNF) en appelant la fonction `negationNormalForm`.
5. Elle itère sur chaque caractère de la formule convertie:
	- Si le caractère est une lettre (variable), elle vérifie si la variable a déjà été rencontrée. Si c'est le cas, elle récupère l'ensemble correspondant dans le powerset `sets`, le pousse dans la pile. Sinon elle crée une nouvelle variable, récupère l'ensemble correspondant dans le powerset `sets` et le pousse dans la pile, tout en ajoutant la variable au vecteur `variables`.
	- Si le caractère est une opération de négation `!`, elle récupère l'ensemble qui se trouve en haut de la pile, effectue la négation en utilisant l'ensemble universel et place le résultat sur la pile.
	- Si le caractère est une opération (`&`, `|`, `^`, `=`, `>`), elle récupère les deux ensembles supérieurs de la pile, effectue l'opération correspondante et pousse le résultat dans la pile.
6. À la fin de l'itération, l'ensemble résultant se trouve au sommet de la pile, et il est renvoyé.

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

La fonction `map` est utilisée pour mapper deux valeurs entieres non signées (`x` et `y`) en une valeur réelle dans la plage [0, 1].

1. Elle combine les valeurs `x` et `y` en une valeur de entière de 64 bits en utilisant un décalage de bits et un **OU** logique.
2. Ensuite, elle convertit cette valeur entière en un double et la divise par la constante `MAX_VALUE` pour obtenir une valeur réelle dans la plage [0, 1].
3. La valeur réelle est renvoyée.

La fonction `reverseMap` effectue l'opération inverse de la fonction `map`.

1. Elle prend en entrée une valeur réelle dans la plage [0, 1].
2. La valeur d'abord est multipliée par la constante `MAX_VALUE` pour obtenir une valeur entière de 64 bits.
3. Ensuite, cette valeur entière est utilisée pour extraire les valeurs `x` et `y` à l'aide d'opérations de décalage de bits et de masquage.
4. Les valeurs `x` et `y` sont stockées dans une structure `t_vec2s` et renvoyées.
