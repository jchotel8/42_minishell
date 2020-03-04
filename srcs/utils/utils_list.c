/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 05:02:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/23 20:09:18 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//toutes ces fonctions pourront être rajoutées dans la libft

t_list	*ft_lstcrea(int i, ...)
{
	va_list		va;
	t_list *first = NULL;

	va_start(va, i);
	while (i-- > 0)
	{
		ft_lstadd_back(&first, ft_lstnew(va_arg(va, void *)));
	}
	va_end(va);
	return (first);
}

t_list	*ft_array_to_lst(char **array)
{
	t_list	*first = NULL;
	int		i;

	i = 0;
	while (array && array[i])
	{
		ft_lstadd_back(&first, ft_lstnew(array[i]));
		i++;
	}
	return (first);
}

t_list	*ft_add_array_to_list(t_list *first, char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		ft_lstadd_back(&first, ft_lstnew(array[i]));
		i++;
	}
	return (first);
}

char	**ft_lst_to_array(t_list *lst)
{
	char	**new;
	int		i;

	if (!(new = (char **)malloc(sizeof(char *) * ft_lstsize(lst) + 1)))
		return(NULL);

	i = 0;
	while (lst)
	{
		new[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	new[i] = 0;
	return (new);
}

void	ft_print_array(char **array, char *text, int flag)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (flag == 1)
			printf("%s[%d] %s.\n", text, i, array[i]);
		else
			printf("%s%s.\n", text, array[i]);
		i++;
	}
}

void	ft_list_print(t_list *ptr, int flag)
{
	int	i = 0;

	if (ptr)
	{
		flag == 1 ? printf("[%d] : %s\n", i, ptr->content) :
		printf("%s\n", ptr->content);
		while(ptr->next)
		{
			ptr = ptr->next;
			i++;
			flag == 1 ? printf("[%d] : %s\n", i, ptr->content) :
			printf("%s\n", ptr->content);
		}
	}
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*remove;
	t_list	*current;

	current = *begin_list;
	while (current && current->next)
	{
		if ((*cmp)(current->next->content, data_ref) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free(remove);
		}
		current = current->next;
	}
	current = *begin_list;
	if (current && (*cmp)(current->content, data_ref) == 0)
	{
		*begin_list = current->next;
		free(current);
	}
}

int	ft_arraysize(char **array)
{
	int	i;

	i = -1;
	if (array)
		i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

void ft_freearray(char **array, int i)
{
	while (i--)
	{
		free(array[i]);
	}
}

int		ft_strncmp_auto(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, strlen(s2)));
}

t_list	*ft_list_sort(t_list *lst, int (*cmp)())
{
	void	*tmp_data;
	t_list	*tmp_lst;

	tmp_lst = lst;
	while (lst->next)
	{
		if (((*cmp)(lst->content, lst->next->content)) > 0)
		{
			tmp_data = lst->content;
			lst->content = lst->next->content;
			lst->next->content = tmp_data;
			lst = tmp_lst;
		}
		else
			lst = lst->next;
	}
	lst = tmp_lst;
	return (lst);
}

void	test_utils(void)
{
	t_list *list = ft_lstcrea(5, "arg1", "pasarg2", "arg3", "a", "arg0");
	ft_printf("LIST W/ INFO.........\n");
	ft_list_print(list, 1);
	ft_printf("LIST.........\n");
	ft_list_print(list, 0);

	ft_printf("ARRAY W/ INFO.........\n");
	char **array = ft_lst_to_array(list);
	ft_print_array(array, "array :", 1);

	ft_printf("ARRAY.........\n");
	ft_print_array(array, "", 0);
	t_list *new = ft_array_to_lst(array);

	ft_printf("LIST W/ INFO.........\n");
	ft_list_print(new, 1);
	ft_printf("LIST.........\n");
	ft_list_print(new, 0);

	ft_printf("LIST SORT .........\n");
	ft_printf("strcmp.........\n");
	ft_list_sort(new, ft_strcmp);
	ft_list_print(new, 1);

	ft_printf("LIST REMOVE IF.........\n");
	ft_printf("strcmp.........\n");
	//printf("same : %d\tdiff : %d\n", ft_strcmp("arg", "arg"), ft_strcmp("arg1", "arg"));
	//ft_printf("strncmp.........\n");
	//printf("same : %d\tdiff : %d\n", ft_strncmp("arg", "arg", 2), ft_strncmp("arg1", "arg", 4));
	ft_list_remove_if(&list, &"arg", ft_strncmp_auto);
	ft_list_print(list, 0);
}
