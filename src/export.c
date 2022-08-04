/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:58:40 by alukongo          #+#    #+#             */
/*   Updated: 2022/08/02 01:46:01 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

t_list *ft_cpy_env(t_list *dest, t_list *src, int src_size)
{
	t_list *list1;
	t_list *list2;
	
	list1 = dest;
	list2 = src;
	while (src_size)
	{
		list1 = ft_lstnew2(list2->content, list2->result);
		if (!list1)
			return(0);
		ft_lstadd_back(&dest, list1);
		list2 = list2->next;
		src_size--;
	}
	return (dest);
}

int cmp(void *content, void *content_ref)
{
	int i;
	char *str;
	char *str2;

	str2 = content_ref;
	str = content;
	i = 0;
	while (i < ft_strlen(str) && i < ft_strlen(str2))
	{
		if (str[i] > str2[i])
			return (1);
		else if (str[i] < str2[i])
			return (-1);
		i++;
	}
	return (-1);
}

void ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list *current;
	void *next_list_content;
	void *next_list_result;
	current = *begin_list;
	while (current->next)
	{
		if ((*cmp)(current->content, current->next->content) > 0)
		{
			next_list_content = current->content;
			next_list_result = current->result;
			current->content = current->next->content;
			current->result = current->next->result;
			current->next->content = next_list_content;
			current->next->result = next_list_result;
			current = *begin_list; 
		}
		else
			current = current->next;
	}
}

void my_export(t_list *env)
{
	t_list *cpy_env;
	int size;
	
	size = ft_lstsize(env);
	cpy_env = NULL;
	cpy_env = ft_cpy_env(cpy_env, env, size);
	ft_list_sort(&cpy_env, cmp);
	ft_env(cpy_env);
}
