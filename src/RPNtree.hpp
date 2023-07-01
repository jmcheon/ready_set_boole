#ifndef RPNTREE_HPP
#define RPNTREE_HPP
#include <iostream>
#include <string>
#include <memory>
#include <stack>
#include <vector>

class RPNNode
{
	private:
	    char					m_value;
	public:
	    std::unique_ptr<RPNNode>	m_left;
	    std::unique_ptr<RPNNode>	m_right;

		RPNNode(const char& value, std::unique_ptr<RPNNode> left, std::unique_ptr<RPNNode> right) : m_value(value), m_left(std::move(left)), m_right(std::move(right)) {}
		explicit RPNNode(const char& value) : m_value(value), m_left(nullptr), m_right(nullptr) { }

		std::unique_ptr<RPNNode> clone()
		{
			std::unique_ptr<RPNNode> new_node = std::make_unique<RPNNode>(m_value);
			if (m_left)
			    new_node->m_left = (m_left->clone());
			if (m_right)
			    new_node->m_right = (m_right->clone());
			return new_node;
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

std::unique_ptr<RPNNode>	buildTree(const std::string& formula);
std::unique_ptr<RPNNode>	applyDistributiveLaw(std::unique_ptr<RPNNode>& root);
std::string					postorder(std::unique_ptr<RPNNode>& root);
std::string					inorder(std::unique_ptr<RPNNode>& root);

void	printNode(const RPNNode* node);
void	printTree(const RPNNode* node, bool leftview=false);
void	printTreeRightview(const std::string& prefix, const RPNNode* node, bool is_left);
void	printTreeLeftview(const std::string& prefix, const RPNNode* node, bool is_left);

#endif
