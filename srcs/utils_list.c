/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 05:02:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 07:37:28 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//toutes ces fonctions pourront être rajoutées dans la libft

void	ft_list_print(t_list *ptr, int flag)
{
	int i = 0;

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

t_list	*ft_lstcrea(int i, ...)
{
	va_list va;
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
	t_list *first = NULL;
	int i;

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
	char **new;
	int i;

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
	int i;

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

int		ft_strncmp_auto(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, strlen(s2)));
}

void	test_utils(void)
{
	t_list *list = ft_lstcrea(3, "arg1", "pasarg2", "arg3");
	ft_printf("LIST W/ INFO.........\n");
	ft_list_print(list, 1);
	ft_printf("LIST.........\n");
	ft_list_print(list, 0);
	char **array = ft_lst_to_array(list);
	ft_printf("ARRAY W/ INFO.........\n");
	ft_print_array(array, "array :", 1);
	ft_printf("ARRAY.........\n");
	ft_print_array(array, "", 0);
	t_list *new = ft_array_to_lst(array);
	ft_printf("LIST W/ INFO.........\n");
	ft_list_print(new, 1);
	ft_printf("LIST.........\n");
	ft_list_print(new, 0);
	ft_printf("LIST REMOVE IF.........\n");
	ft_printf("strcmp.........\n");
	printf("same : %d\tdiff : %d\n", ft_strcmp("arg", "arg"), ft_strcmp("arg1", "arg"));
	ft_printf("strncmp.........\n");
	printf("same : %d\tdiff : %d\n", ft_strncmp("arg", "arg", 2), ft_strncmp("arg1", "arg", 4));
	ft_list_remove_if(&list, &"arg", ft_strncmp_auto);
	ft_list_print(list, 0);
}
