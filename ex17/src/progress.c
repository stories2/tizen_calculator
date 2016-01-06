#include "ex17.h"

char stack[100],database[100][100],buffer[100];

static void calculate(char data[] , char screen_buffer[])
{
	int i, t, str_length, top = 0, save_point = 1;
	char temp;
	bool first_minus = true;

	for (i = 0; i < 100; i += 1)
	{
		stack[i] = 0;
		for (t = 0; t < 100; t += 1)
		{
			database[i][t] = 0;
		}
	}

	t = 0;
	str_length = strlen(data);
	for (i = 0; i < str_length-1; i += 1)
	{
		if (('0' <= data[i] && data[i] <= '9') || data[i] == '.')
		{
			database[save_point][t] = data[i];
			t += 1;
			first_minus = false;
		}
		else
		{
			if (first_minus == true && (data[i] == '-' || data[i] == '+'))
			{
				save_point += 1;
				database[save_point][0] = '0';
			}
			for (t = top; t >= 1; t -= 1)
			{
				if (check_permission(data[i]) == 5)//잘못된 기호
				{
					break;
				}
				else if (check_permission(stack[top]) <= check_permission(data[i]))
				{
					if (data[i] != '(' && stack[top] != '(')
					{
						temp = pop(&top);
						if (temp != '(')
						{
							save_point += 1;
							database[save_point][0] = temp;
						}
						if (temp == '(' && data[i] == ')')//괄호닫기가 괄호 열기를 찾음
						{
							break;
						}
					}
					else if (data[i] == ')' && stack[top] == '(')
					{
						temp = pop(&top);
						break;
					}
				}

			}
			if (data[i] != ')')
			{
				push(data[i], &top);
			}
			t = 0;
			save_point += 1;
		}
	}

	while (top>0)
	{
		save_point += 1;
		database[save_point][0] = pop(&top);
	}

	int point_a = 0, point_b = 0;
	bool part_a, part_b,order;
	while (true)
	{
		part_a = false;
		part_b = false;
		order = false;
		for (i = 1; i <= save_point; i += 1)
		{
			if (('0' <= database[i][0] && database[i][0] <= '9') || (database[i][0] == '-' && strlen(database[i]) > 1))
			{
				if (part_a == true && part_b == true)
				{
					point_a = point_b;
					point_b = i;
				}
				if (part_a == false)
				{
					part_a = true;
					point_a = i;
				}
				else if (part_b == false)
				{
					part_b = true;
					point_b = i;
				}
			}
			if ((database[i][0] == '-' || database[i][0] == '+' || database[i][0] == '*' || database[i][0] == '/') && strlen(database[i]) == 1)
			{
				double a, b;
				if (part_a == true && part_b == true)
				{
					int length = strlen(database[point_a]), swap_point, ten = 1;
					bool found = false,minus = false;
					if (database[point_a][0] == '-')
					{
						for (t = 0; t < length; t += 1)
						{
							database[point_a][t] = database[point_a][t + 1];
							database[point_a][t + 1] = 0;
						}
						a = atoi(database[point_a]);
						minus = true;
					}
					else
					{
						a = atoi(database[point_a]);
						minus = false;
					}
					length = strlen(database[point_a]);
					for (t = 0; t<length; t += 1)
					{
						if (database[point_a][t] == '.')
						{
							found = true;
							swap_point = t;
							break;
						}
					}
					if (found == true)
					{
						for (t = 0; t<length - swap_point; t += 1)
						{
							ten = ten * 10;
							database[point_a][t] = database[point_a][swap_point + t + 1];
						}
						ten = ten / 10;
						a = a + (double)atoi(database[point_a])/ten;
					}
					if (minus == true)
					{
						a = a * -1;
					}

					minus = false;
					if (database[point_b][0] == '-')
					{
						for (t = 0; t < length; t += 1)
						{
							database[point_b][t] = database[point_b][t + 1];
							database[point_b][t + 1] = 0;
						}
						b = atoi(database[point_b]);
						minus = true;
					}
					else
					{
						b = atoi(database[point_b]);
						minus = false;
					}
					found = false;
					length = strlen(database[point_b]);
					ten = 1;
					for (t = 0; t<length; t += 1)
					{
						if (database[point_b][t] == '.')
						{
							found = true;
							swap_point = t;
							break;
						}
					}
					if (found == true)
					{
						for (t = 0; t<length - swap_point; t += 1)
						{
							ten = ten * 10;
							database[point_b][t] = database[point_b][swap_point + t + 1];
						}
						ten = ten / 10;
						b = b + (double)atoi(database[point_b])/ten;
					}
					if (minus == true)
					{
						b = b * -1;
					}

					sprintf(buffer,"%f %c %f",a,database[i][0],b);

					order = true;
					switch (database[i][0])
					{
					case '+':
						sprintf(database[point_a], "%f", (a + b));
						sprintf(database[point_b], "");
						break;
					case '-':
						sprintf(database[point_a], "%f", (a - b));
						sprintf(database[point_b], "");
						break;
					case '*':
						sprintf(database[point_a], "%f", (a * b));
						sprintf(database[point_b], "");
						break;
					case '/':
						sprintf(database[point_a], "%f", (a / b));
						sprintf(database[point_b], "");
						break;
					}
					database[i][0] = 0;
					sprintf(buffer,"%s = %s",buffer,database[point_a]);
					dlog_print(DLOG_INFO,"ex17",buffer);
					break;
				}
				else
				{
					part_a = false;
					part_b = false;
				}
			}
		}
		if (order == false)
		{
			break;
		}
	}

	double result;
	int length = strlen(database[point_a]);
	bool minus = false;
	if (database[point_a][0] == '-')
	{
		for (i = 0; i < length; i += 1)
		{
			database[point_a][i] = database[point_a][i+1];
			database[point_a][i + 1] = 0;
		}
		result = atoi(database[point_a]);
		minus = true;
	}
	else
	{
		result = atoi(database[point_a]);
	}

	bool found = false;
	int swap_point,ten = 1;
	length = strlen(database[point_a]);
	for (t = 0; t<length; t += 1)
	{
		if (database[point_a][t] == '.')
		{
			found = true;
			swap_point = t;
			break;
		}
	}
	if (found == true)
	{
		for (t = 0; t<length - swap_point; t += 1)
		{
			ten = ten * 10;
			database[point_a][t] = database[point_a][swap_point + t + 1];
		}
		ten = ten / 10;
		result = result + (double)atoi(database[point_a])/ten;
	}

	int result_check = (int)result;
	if (result - result_check != 0)
	{
		if (minus == true)
		{
			result = result * -1;
		}
		//printf("%f\n", result);
		sprintf(buffer,"result : %f",result);
		dlog_print(DLOG_INFO,"ex17",buffer);
		sprintf(screen_buffer,"%s%f",screen_buffer,result);
	}
	else
	{
		if (minus == true)
		{
			result_check = result_check * -1;
		}
		//printf("%d\n", result_check);
		sprintf(buffer,"result : %d",result_check);
		dlog_print(DLOG_INFO,"ex17",buffer);
		sprintf(screen_buffer,"%s%d",screen_buffer,result_check);
	}
}

static void push(char target , int *push_point)
{
	*push_point = *push_point + 1;
	stack[*push_point] = target;
}

static char pop(int *pop_point)
{
	if (*pop_point > 0)
	{
		char get = stack[*pop_point];
		stack[*pop_point] = 0;
		*pop_point = *pop_point - 1;
		return get;
	}
	else
	{
		return 'U';
	}
}

static int check_permission(char target)
{
	if (target == '(')
	{
		return 1;
	}
	else if (target == '+' || target == '-')
	{
		return 3;
	}
	else if (target == '*' || target == '/')
	{
		return 2;
	}
	else if (target == ')')
	{
		return 4;
	}
	else
	{
		return 5;
	}
}
