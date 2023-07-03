#include "RPNtree.hpp"

bool	checkFormula(const std::string& formula, bool variable, bool print)
{
	std::unique_ptr<RPNNode> rpn;
	try
	{
 		rpn = buildTree(formula, variable);
		if (print)
		{
			std::cout << "formula: ";
			std::cout << preorder(rpn) << std::endl;
        	//printNode(rpn.get());
        	printTree(rpn.get(), true);
			std::cout << std::endl;
		}
    }
	catch (const std::runtime_error& e)
	{
        std::cerr << "Error: " << e.what() << std::endl;
		return false;
    }
	return true;
}

std::unique_ptr<RPNNode> buildTree(const std::string& formula, bool variable)
{
	std::stack<std::unique_ptr<RPNNode> > stack;
	
	for (char c : formula)
	{
		if ((c >= 'A' && c <= 'Z') || (c == '1' || c == '0'))
		{
			if ((variable && !(c >= 'A' && c <= 'Z'))
				|| (!variable && !(c == '1' || c == '0')))
				throw std::runtime_error("Invalid formula: Unexpected symbol");
			std::unique_ptr<RPNNode> new_node = std::make_unique<RPNNode>(c);
			stack.push(std::move(new_node));
		}
		else if (c == '!')
		{
			if (stack.empty())
				throw std::runtime_error("Invalid formula: Not enough operands");
			std::unique_ptr<RPNNode> new_node = std::make_unique<RPNNode>(c);
			new_node->m_left = std::move(stack.top());
			new_node->m_left->m_parent = new_node->clone();
			stack.pop();
			stack.push(std::move(new_node));
		}
		else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=')
		{
			if (stack.size() < 2)
				throw std::runtime_error("Invalid formula: Not enough operands");

			std::unique_ptr<RPNNode> new_node = std::make_unique<RPNNode>(c);

			new_node->m_left = std::move(stack.top());
			stack.pop();

			new_node->m_right = std::move(stack.top());
			//std::cout << new_node->m_parent->getValue() << std::endl;
			stack.pop();
			new_node->m_left->m_parent = new_node->clone();
			new_node->m_right->m_parent = new_node->clone();

			stack.push(std::move(new_node));
		}
		else
			throw std::runtime_error("Invalid formula: Unexpected symbol");
	}
	if (stack.size() != 1)
		throw std::runtime_error("Invalid formula: Too many operands");
	return std::move(stack.top());
}

std::string	preorder(std::unique_ptr<RPNNode>& root)
{
	std::string output;

    if (root == nullptr)
        return output;

    output += preorder(root->m_right);
    output += preorder(root->m_left);
    output += root->getValue();
	return output;
}

std::string	postorder(std::unique_ptr<RPNNode>& root)
{
	std::string output;

    if (root == nullptr)
        return output;

    output += postorder(root->m_left);
    output += postorder(root->m_right);
    output += root->getValue();
	return output;
}

std::string	inorder(std::unique_ptr<RPNNode>& root)
{
	std::string output;

	if (!root)
		return output;
	
	if (isupper(root->getValue()))
		output += root->getValue();
	output += inorder(root->m_left);
	
	if (!isupper(root->getValue()))
		output += root->getValue();
	output += inorder(root->m_right);
	return output;
}

std::unique_ptr<RPNNode> distribute(std::unique_ptr<RPNNode>& a, std::unique_ptr<RPNNode>& b, std::unique_ptr<RPNNode>& c, std::unique_ptr<RPNNode>& d, bool left)
{
	std::cout << "a:" << a->getValue() << std::endl;
	printTree(a.get(), true);
	std::cout << "b:" << b->getValue() << std::endl;
	printTree(b.get(), true);
	std::cout << "c:" << c->getValue() << std::endl;
	printTree(c.get(), true);
	if (d)
	{
		std::cout << "d:" << d->getValue() << std::endl;
		printTree(d.get(), true);
	}

    std::unique_ptr<RPNNode> new_root = std::make_unique<RPNNode>('&');

	if (d)
	{
    	std::unique_ptr<RPNNode> temp1 = std::make_unique<RPNNode>('&');
    	std::unique_ptr<RPNNode> temp2 = std::make_unique<RPNNode>('&');

    	temp1->m_left = std::make_unique<RPNNode>('|', a->clone(), c->clone(), new_root->clone());
    	temp1->m_right = std::make_unique<RPNNode>('|', a->clone(), d->clone(), new_root->clone());
    	//temp2->m_left = std::make_unique<RPNNode>('|', b->clone(), c->clone(), new_root->clone());
    	temp2->m_left = std::move(temp1);
    	temp2->m_right = std::make_unique<RPNNode>('|', b->clone(), d->clone(), new_root->clone());

		new_root->m_left = std::move(temp2);
		new_root->m_right = std::make_unique<RPNNode>('|', b->clone(), c->clone(), new_root->clone());
	}
	else if (left)
	{
    	new_root->m_left = std::make_unique<RPNNode>('|', std::move(b), a->clone(), new_root->clone());
    	new_root->m_right = std::make_unique<RPNNode>('|', std::move(c), a->clone(), new_root->clone());
	}
	else
	{
    	new_root->m_left = std::make_unique<RPNNode>('|', a->clone(), std::move(b), new_root->clone());
    	new_root->m_right = std::make_unique<RPNNode>('|', a->clone(), std::move(c), new_root->clone());
	}
	std::cout << "new:" << new_root->getValue() << std::endl;
    return new_root;
}

bool isDistributable(const std::unique_ptr<RPNNode>& root)
{
    if (!root)
		return false;
	/*
	if (root->m_left)
		std::cout << "left:" << root->m_left->getValue() << std::endl;
	if (root->m_right)
		std::cout << "right:" << root->m_right->getValue() << std::endl;
	*/
    return (root->getValue() == '|' && ((root->m_left && root->m_left->getValue() == '&') || (root->m_right && root->m_right->getValue() == '&')));
}

std::unique_ptr<RPNNode> applyDistributiveLaw(std::unique_ptr<RPNNode>& root)
{
	bool	left = false;
    if (!root)
		return nullptr;
	if (root->m_left)
		root->m_left = applyDistributiveLaw(root->m_left);
	if (root->m_right)
		root->m_right = applyDistributiveLaw(root->m_right);

    if (isDistributable(root)) {
        std::unique_ptr<RPNNode> a, b, c, d;

		std::cout << "value:" << root->getValue() << std::endl;

        if ((root->m_left && root->m_left->getValue() == '&') 
			&& (root->m_right && root->m_right->getValue() == '&'))
		{
			//std::cout << root->m_parent->getValue() << std::endl;
			if (root->m_parent)
			{
				if (root->m_parent->m_right)
					std::cout << "r-p-r: " << root->m_parent->m_right->getValue() << std::endl;
				if (root->m_parent->m_left)
					std::cout << "r-p-l: " << root->m_parent->m_left->getValue() << std::endl;
			//a = std::move(root->m_parent->m_right);
			}
			//a = std::move(root->m_parent);
			a = std::move(root->m_right->m_right);
			b = std::move(root->m_right->m_left);
			c = std::move(root->m_left->m_right);
			d = std::move(root->m_left->m_left);
		}
        else if (root->m_left && root->m_left->getValue() == '&')
		{
			left = true;
			std::cout << "1left:" << root->m_left->getValue() << std::endl;
			std::cout << "1right:" << root->m_right->getValue() << std::endl;
			if (isupper(root->m_right->getValue()))
		    	a = std::move(root->m_right);
			else
		    	a = std::move(root->m_right->m_right);

			if (root->m_left->m_left)
			{
				std::cout << "1left-left:" << root->m_left->m_left->getValue() << std::endl;
		    	b = std::move(root->m_left->m_left);
			}
			else
			{
				std::cout << "1left:" << root->m_left->getValue() << std::endl;
		    	//b = std::move(root->m_left);
				b = root->m_left->clone();
			}

			if (root->m_left->m_right)
		    	c = std::move(root->m_left->m_right);
			else
				c = root->m_right->m_left->clone();
        }
		else if (root->m_right && root->m_right->getValue() == '&')
		{
			if (root->m_left)
				std::cout << "2left:" << root->m_left->getValue() << std::endl;
			if (root->m_right)
				std::cout << "2right:" << root->m_right->getValue() << std::endl;
		    a = std::move(root->m_left);
		    b = std::move(root->m_right->m_left);
		    c = std::move(root->m_right->m_right);
			/*
        } else if (root->m_left && root->m_left->getValue() == '|') {
			    a = std::move(root->m_right);
			    b = std::move(root->m_left->m_left);
			    c = std::move(root->m_left->m_right);
				*/
        }
		else
		{
			std::cout << "3left:" << root->m_left->getValue() << std::endl;
			std::cout << "3right:" << root->m_right->getValue() << std::endl;

			a = std::move(root->m_left);
			b = std::move(root->m_right->m_left);
			c = std::move(root->m_right->m_right);
        }

        root = distribute(a, b, c, d, left);
		printTree(root.get(), true);
		//std::cout << postorder(root) << std::endl;
		std::cout << BLUE << preorder(root) << FIN << std::endl;
		/*
		if (root->m_left)
			root->m_left = applyDistributiveLaw(root->m_left);
		if (root->m_right)
			root->m_right = applyDistributiveLaw(root->m_right);
			*/
    }

    return std::move(root);
}

/*
std::unique_ptr<RPNNode> applyDistributiveLaw0(std::unique_ptr<RPNNode>& root)
{
    if (!root)
		return nullptr;
	if (root->m_left)
		root->m_left = applyDistributiveLaw(root->m_left);
	if (root->m_right)
		root->m_right = applyDistributiveLaw(root->m_right);

    if (isDistributable(root)) {
        std::unique_ptr<RPNNode> a, b, c;

		std::cout << "value:" << root->getValue() << std::endl;
        if (root->m_left && root->m_left->getValue() == '&') {
				std::cout << "1left:" << root->m_left->getValue() << std::endl;
				if (root->m_right)
					std::cout << "1right:" << root->m_right->getValue() << std::endl;
			    a = std::move(root->m_right);
				//std::cout << "right:" << root->m_right->getValue() << std::endl;
			    b = std::move(root->m_left->m_left);
			    c = std::move(root->m_left->m_right);
        } else if (root->m_right && root->m_right->getValue() == '&') {
				std::cout << "2left:" << root->m_left->getValue() << std::endl;
				std::cout << "2right:" << root->m_right->getValue() << std::endl;
				if (isupper(root->m_right->getValue()))
			    	a = std::move(root->m_right);
				else
			    	a = std::move(root->m_right->m_right);
				if (root->m_left->m_left)
				{
					std::cout << "2left-left:" << root->m_left->m_left->getValue() << std::endl;
			    	b = std::move(root->m_left->m_left);
				}
				else
				{
					std::cout << "2left:" << root->m_left->getValue() << std::endl;
			    	//b = std::move(root->m_left);
					b = root->m_left->clone();
				}
				if (root->m_left->m_right)
			    	c = std::move(root->m_left->m_right);
				else
					c = root->m_right->m_left->clone();
        } else { // (root->m_right && root->m_right->getValue() == '|')
			    a = std::move(root->m_left);
			    b = std::move(root->m_right->m_left);
			    c = std::move(root->m_right->m_right);
        }

        root = distribute(a, b, c, true);
		printTree(root.get(), true);
		std::cout << postorder(root) << std::endl;
		if (root->m_left)
			root->m_left = applyDistributiveLaw(root->m_left);
		if (root->m_right)
			root->m_right = applyDistributiveLaw(root->m_right);
    }

    return std::move(root);
}
*/

void	printNode(const RPNNode* node)
{
	if (node)
		node->print();
	std::cout << std::endl;
}

void	printTreeLeftview(const std::string& prefix, const RPNNode* node, bool is_left)
{
    if( node != nullptr )
    {
        std::cout << prefix;
        std::cout << (is_left ? "└─" : "├─" );

		node->traverse();
    	std::cout << std::endl;
        printTreeLeftview(prefix + (is_left ? "   " : "│  "), node->getRight(), false);
        printTreeLeftview(prefix + (is_left ? "   " : "│  "), node->getLeft(), true);
    }
}

void	printTreeRightview(const std::string& prefix, const RPNNode* node, bool is_left)
{
    if( node != nullptr )
    {
        std::cout << prefix;
        std::cout << (is_left ? "├─" : "└─" );

		node->traverse();
    	std::cout << std::endl;
        printTreeRightview(prefix + (is_left ? "│  " : "   "), node->getLeft(), true);
        printTreeRightview(prefix + (is_left ? "│  " : "   "), node->getRight(), false);
    }
}

void	printTree(const RPNNode* node, bool leftview)
{
	if (leftview)
    	printTreeLeftview("", node, true);
	else
    	printTreeRightview("", node, false);
}
