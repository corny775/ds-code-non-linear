#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int PR_NUM = 202311094;
char ROLL_NUM[] = "23B-CO-016";
void footer()
{
	printf("\n______________________________\n");
	printf("PR NUMBER: %d\n", PR_NUM);
	printf("ROLL NUMBER: %s", ROLL_NUM);
	printf("\n-------------------------------\n\n");
}
struct node
{
	int info;
	struct node *left;
	struct node *right;
	bool lthread;
	bool rthread;
};
struct node *in_succ(struct node *ptr)
{
	if (ptr->rthread == true)
		return ptr->right;
	else
	{
		ptr = ptr->right;
		while (ptr->lthread == false)
			ptr = ptr->left;

		return ptr;
	}
}
struct node *in_pred(struct node *ptr)
{
	if (ptr->lthread == true)
		return ptr->left;
	else
	{
		ptr = ptr->right;
		while (ptr->rthread == false)
			ptr = ptr->left;

		return ptr;
	}
}
struct node *insert(struct node *root, int ikey)
{
	struct node *tmp, *par, *ptr;
	int found = 0;
	ptr = root;
	par = NULL;
	while (ptr != NULL)
	{
		if (ikey == ptr->info)
		{
			found = 1;
			break;
		}
		par = ptr;
		if (ikey < ptr->info)
		{
			if (ptr->lthread == false)
				ptr = ptr->left;
			else
				break;
		}
		else
		{
			if (ptr->rthread == false)
				ptr = ptr->right;
			else
				break;
		}
	}
	if (found)
	{
		printf("Duplicate key\n");
	}
	else
	{
		tmp = (struct node *)malloc(sizeof(struct node));
		tmp->info = ikey;
		tmp->lthread = true;
		tmp->rthread = true;
		if (par == NULL)
		{
			root = tmp;
			tmp->left = NULL;
			tmp->right = NULL;
		}
		else if (ikey < par->info)
		{
			tmp->left = par->left;
			tmp->right = par;
			par->lthread = false;
			par->left = tmp;
		}
		else
		{
			tmp->right = par->right;
			tmp->left = par;
			par->rthread = false;
			par->right = tmp;
		}
	}
	return root;
}
struct node *case_a(struct node *root, struct node *par, struct node *ptr)
{
	if (ptr == NULL)
		root = NULL;
	else if (par->left == ptr)
	{
		par->lthread = true;
		par->left = ptr->left;
	}
	else
	{
		par->rthread = true;
		par->right = ptr->right;
	}
	free(ptr);
	return root;
}
struct node *case_b(struct node *root, struct node *par, struct node *ptr)
{
	struct node *child, *p, *s;
	if (ptr->lthread == false)
		child = ptr->left;
	else
		child = ptr->right;
	if (par == NULL)
		root = child;
	else if (par->left == ptr)
		par->left = child;
	else
		par->right = child;
	s = in_succ(ptr);
	p = in_pred(ptr);
	if (ptr->lthread == false)
		p->right = s;
	else if (ptr->rthread == false)
		s->left = p;
	free(ptr);
	return root;
}
struct node *case_c(struct node *root, struct node *par, struct node *ptr)
{
	struct node *succ, *parsucc;
	succ = ptr->right;
	while (succ->left != NULL)
	{
		parsucc = succ;
		succ = succ->left;
	}
	ptr->info = succ->info;
	if (succ->lthread == true && succ->rthread == true)
		root = case_a(root, parsucc, succ);
	else
		root = case_b(root, parsucc, succ);
	return root;
}
struct node *search_t(struct node *root, int dkey)
{
	struct node *par, *ptr;
	int found = 0;
	ptr = root;
	par = NULL;
	while (ptr != NULL)
	{
		if (dkey == ptr->info)
		{
			found = 1;
			printf("the key is found ");
			break;
		}
		par = ptr;
		if (dkey < ptr->info)
		{
			if (ptr->lthread == false)
				ptr = ptr->left;
			else
				break;
		}
		else
		{
			if (ptr->rthread == false)
				ptr = ptr->right;
			else
				break;
		}
	}
	if (found == 0)
		printf("The element is not found");
}
struct node *del(struct node *root, int dkey)
{
	struct node *par, *ptr;
	int found = 0;
	ptr = root;
	par = NULL;
	while (ptr != NULL)
	{
		if (dkey == ptr->info)
		{
			found = 1;
			break;
		}
		par = ptr;
		if (dkey < ptr->info)
		{
			if (ptr->lthread == false)
				ptr = ptr->left;
			else
				break;
		}
		else
		{
			if (ptr->rthread == false)
				ptr = ptr->right;
			else
				break;
		}
	}
	if (found == 0)
		printf("not present");
	else if (ptr->lthread == false && ptr->rthread == false)
		root = case_c(root, par, ptr);
	else if (ptr->lthread == false)
		root = case_b(root, par, ptr);
	else if (ptr->rthread == false)
		root = case_b(root, par, ptr);
	else
		root = case_a(root, par, ptr);
	return root;
}
void preorder(struct node *root)
{
	if (root == NULL)
		return;
	struct node *ptr = root;
	while (ptr != NULL)
	{
		printf("%d ", ptr->info);
		if (ptr->lthread == false)
		{
			ptr = ptr->left;
		}
		else
		{
			while (ptr != NULL && ptr->rthread == true)
			{
				ptr = ptr->right;
			}
			if (ptr != NULL)
			{
				ptr = ptr->right;
			}
		}
	}
}
void inorder(struct node *root)
{
	if (root == NULL)
		return;
	struct node *ptr = root;
	while (ptr->lthread == false)
	{
		ptr = ptr->left;
	}
	while (ptr != NULL)
	{
		printf("%d ", ptr->info);
		ptr = in_succ(ptr);
	}
}
void postorder(struct node *root)
{
	if (root == NULL)
		return;
	if (root->lthread == false)
	{
		postorder(root->left);
	}
	if (root->rthread == false)
	{
		postorder(root->right);
	}
	printf("%d \t", root->info);
}
int main()
{
	footer();
	struct node *root = NULL;
	int n;
	int k;
	int m;
	int l;
	while (1)
	{
		printf("Enter \n 1 for insert \n 2 for delete \n 3 for inorder treversal \n 4 for postorder traversal \n 5 for the preorder traversal \n 6 to exit \n 7 for search");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("Enter the element to insert i the tree");
			scanf("%d", &k);
			root = insert(root, k);
			break;
		case 2:
			printf("Enter the element to delete");
			scanf("%d", &m);
			del(root, m);
			break;
		case 3:
			printf("The inorder traversal is \n");
			inorder(root);
			break;
		case 4:
			printf("The postorder traversal is \n");
			postorder(root);
			break;
		case 5:
			printf("The preorder traversal is \n");
			preorder(root);
			break;
		case 6:
			exit(1);
		case 7:
			printf("Enter the element to search");
			scanf("%d", &l);
			search_t(root, l);
		}
	}
	return 0;
}