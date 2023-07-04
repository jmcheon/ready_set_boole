#ifndef RPNTREE_HPP
#define RPNTREE_HPP
#include <iostream>
#include <string>
#include <memory>
#include <stack>
#include <vector>
#include "exercise.hpp"

# define YELLOW "\033[0;38;5;220m"
# define GREEN "\033[0;38;5;42m"
# define RED "\033[0;38;5;196m"
# define BLUE "\033[0;38;5;21m"
# define PINK "\033[0;38;5;205m"
# define PURPLE "\033[0;38;5;93m"
# define ORANGE "\033[38;5;202m"
# define FIN "\033[0m"

class RPNNode
{
	private:
	    char					m_value;
	public:
	    std::unique_ptr<RPNNode>	m_left;
	    std::unique_ptr<RPNNode>	m_right;
	    std::unique_ptr<RPNNode>	m_parent;

		RPNNode(char value, std::unique_ptr<RPNNode> left, std::unique_ptr<RPNNode> right, std::unique_ptr<RPNNode> parent) 
		: m_value(value), m_left(std::move(left)), m_right(std::move(right)), m_parent(std::move(parent)) {}

		RPNNode(char value, std::unique_ptr<RPNNode> left, std::unique_ptr<RPNNode> right)
		: m_value(value), m_left(std::move(left)), m_right(std::move(right))
		{
			if (m_left)
				m_left->m_parent = std::unique_ptr<RPNNode>(this);
			if (m_right)
				m_right->m_parent = std::unique_ptr<RPNNode>(this);
		}

		RPNNode(char value) : m_value(value), m_left(nullptr), m_right(nullptr), m_parent(nullptr) { }
		RPNNode(char value, std::unique_ptr<RPNNode> parent) : m_value(value), m_parent(std::move(parent)) { }
		RPNNode(const RPNNode& other) : m_value(other.m_value)
		{
		    if (other.m_left) {
		        m_left = std::make_unique<RPNNode>(*other.m_left);
		    }
		    if (other.m_right) {
		        m_right = std::make_unique<RPNNode>(*other.m_right);
		    }
		}

		std::unique_ptr<RPNNode> clone()
		{
			std::unique_ptr<RPNNode> new_node = std::make_unique<RPNNode>(m_value, nullptr);

			if (m_left)
			    new_node->m_left = (m_left->clone());
			if (m_right)
			    new_node->m_right = (m_right->clone());
			return new_node;
    	}

		std::shared_ptr<RPNNode> getSharedNodePtr()
		{
			std::unique_ptr<RPNNode> temp = std::make_unique<RPNNode>(*this);
        	return std::shared_ptr<RPNNode>(std::move(temp));
		}

		char				getValue() const { return m_value; }
		const RPNNode*		getLeft() const { return m_left.get(); }
		const RPNNode*		getRight() const { return m_right.get(); }
		std::unique_ptr<RPNNode>		getUniqueLeft() const
		{
			if (m_left)
				return m_left->clone();
			else
				return nullptr;
		}
		std::unique_ptr<RPNNode>		getUniqueRight() const
		{
			if (m_right)
				return m_right->clone();
			else
				return nullptr;
		}
		void			print() const
		{
    	    if (m_left)
				m_left->print();
    	    if (m_right)
				m_right->print();
			std::cout << m_value;
		}
		void			traverse() const { std::cout << m_value; }

};

std::unique_ptr<RPNNode>	buildTree(const std::string& formula, bool variable = true);
std::unique_ptr<RPNNode>	applyDistributiveLaw(std::unique_ptr<RPNNode>& root);
std::unique_ptr<RPNNode>	applyConjunctionRearrange(std::unique_ptr<RPNNode>& root);
std::string					preorder(std::unique_ptr<RPNNode>& root);
std::string					inorder(std::unique_ptr<RPNNode>& root);
std::string					postorder(std::unique_ptr<RPNNode>& root);

bool	checkFormula(const std::string& formula, bool variable = true, bool print = true);
void	printNode(const RPNNode* node);
void	printTree(const RPNNode* node, bool leftview=false);
void	printTreeRightview(const std::string& prefix, const RPNNode* node, bool is_left);
void	printTreeLeftview(const std::string& prefix, const RPNNode* node, bool is_left);

#endif
