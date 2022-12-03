#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2000

int total_Revenue = 0; //总收入
int flags = 0;         //标志位，用于判断是否继续循环执行

struct bicycle_information
{
    int num;               //单车编号
    char city[20];         //所属城市
    char sign;             //标记(是否租借)(Y or N)
    int price;             //单价(单位:元)
    int riding_number;     //骑行次数
    int total_riding_time; //骑行总时长(单位:小时)
} bicycle[N];

typedef struct date_information //日期结构体
{
    int year;  //年
    int month; //月
    int day;   //日
} Date;        //重命名

typedef struct rent_information //租借信息结构体
{
    Date RentTime;   //租借时间
    Date ReturnTime; //归还时间
    int theRent;     //租金
} Rent;              //重命名租借信息结构体

struct member_information //会员信息结构体
{
    int num;       //会员编号
    char name[20]; //会员名
    char sign;     //名下是否有标记(是否租借)(Y or N)
    Rent rent;     //租借信息
} member[N];

void read_bicycle(char address[]);  //读取单车信息
void write_bicycle(char address[]); //写入单车信息
void read_member(char address[]);   //读取会员信息
void write_member(char address[]);  //写入会员信息
void feature_show_selection();      //功能展示及选择
void add_bicycle_information();     //添加自行车信息
void search_bicycle_information();  //查找自行车信息
void output_bicycle_information();  //输出自行车信息
void the_member_add();              //添加会员信息
void the_member_search();           //查找会员信息
void the_member_delete();           //删除会员信息
void bicycle_rent();                //租借自行车
void bicycle_return();              //归还自行车
int days_between();                 //计算两个日期之间的天数
void bicycle_Scrap();               //报废自行车
void statistical();                 //统计

int main()
{
    read_bicycle("txt/bicycle.txt"); //读取单车信息
    read_member("txt/member.txt");   //读取会员信息
    while (flags == 0)
    {
        feature_show_selection();
    }
    write_bicycle("txt/bicycle.txt"); //写入单车信息
    write_member("txt/member.txt");   //写入会员信息
    return 0;
}

void read_bicycle(char address[]) //读取单车信息文件，形参为文件地址
{
    FILE *fp;
    int i;
    if ((fp = fopen(address, "r")) == NULL) //文件的地址
    {
        printf("文件打开失败！\n");
        exit(1);
    }
    while (fscanf(fp, "%d", &i) != EOF) //读取文件，首先获取编号
    {
        bicycle[i].num = i; //将此编号的单车放在数组的第i个位置
        fscanf(fp, "%s %c %d %d %d", bicycle[i].city, &bicycle[i].sign, &bicycle[i].price, &bicycle[i].riding_number, &bicycle[i].total_riding_time);
    }
    fclose(fp);
}

void write_bicycle(char address[]) //写入单车信息文件，形参为文件地址
{
    FILE *fp;
    int i;
    if ((fp = fopen(address, "w")) == NULL) //文件的地址
    {
        printf("文件打开失败！\n");
        exit(1);
    }
    for (i = 1; i <= N; i++) //输出单车信息
    {
        if (bicycle[i].num != 0) //如果单车编号不为0，则输出到文件中
        {
            fprintf(fp, "%d\t%s\t%c\t%d\t%d\t%d\n", bicycle[i].num, bicycle[i].city, bicycle[i].sign, bicycle[i].price, bicycle[i].riding_number, bicycle[i].total_riding_time);
        }
    }
    fclose(fp);
}

void read_member(char address[]) //读取会员信息文件，形参为文件地址
{
    FILE *fp;
    int i;
    if ((fp = fopen(address, "r")) == NULL) //文件的地址
    {
        printf("文件打开失败！\n");
        exit(1);
    }
    while (fscanf(fp, "%d", &i) != EOF) //读取文件，首先获取编号
    {
        member[i].num = i; //将此编号的会员放在数组的第i个位置
        fscanf(fp, "%s %c %d/%d/%d %d/%d/%d %d", member[i].name, &member[i].sign, &member[i].rent.RentTime.year, &member[i].rent.RentTime.month, &member[i].rent.RentTime.day, &member[i].rent.ReturnTime.year, &member[i].rent.ReturnTime.month, &member[i].rent.ReturnTime.day, &member[i].rent.theRent);
    }
    fclose(fp);
}

void write_member(char address[]) //写入会员信息文件，形参为文件地址
{
    FILE *fp;
    int i;
    if ((fp = fopen(address, "w")) == NULL) //文件的地址
    {
        printf("文件打开失败！\n");
        exit(1);
    }
    for (i = 1; i <= N; i++) //输出会员信息
    {
        if (member[i].num != 0) //如果会员编号不为0，则输出到文件中
        {
            fprintf(fp, "%d\t%s\t%c\t%d/%d/%d\t%d/%d/%d\t%d\n", member[i].num, member[i].name, member[i].sign, member[i].rent.RentTime.year, member[i].rent.RentTime.month, member[i].rent.RentTime.day, member[i].rent.ReturnTime.year, member[i].rent.ReturnTime.month, member[i].rent.ReturnTime.day, member[i].rent.theRent);
        }
    }
    fclose(fp);
}

void feature_show_selection() //制作一个窗口，显示功能选择
{
    int n, i;
    printf("********************\n"); //功能展示
    printf("* 1.新单车购入 \n");
    printf("* 2.单车查询 \n");
    printf("* 3.单车租借 \n");
    printf("* 4.单车归还 \n");
    printf("* 5.单车报废 \n");
    printf("* 6.统计 \n");
    printf("* 7.会员相关 \n");
    printf("* 8.退出 \n");
    printf("********************\n");
    scanf("%d", &n);
    switch (n) //根据选择的功能，调用相应的函数
    {
    case 1:
        printf("********************\n");
        add_bicycle_information();
        break;
    case 2:
        printf("********************\n");
        search_bicycle_information();
        break;
    case 3:
        printf("********************\n");
        bicycle_rent();
        break;
    case 4:
        printf("********************\n");
        bicycle_return();
        break;
    case 5:
        printf("********************\n");
        bicycle_Scrap();
        break;
    case 6:
        printf("********************\n");
        statistical();
        break;
    case 7:
        printf("********************\n");
        printf("1.会员信息查询\n");
        printf("2.会员注册\n");
        printf("3.会员注销\n");
        printf("********************\n");
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            printf("********************\n");
            the_member_search();
            break;
        case 2:
            printf("********************\n");
            the_member_add();
            break;
        case 3:
            printf("********************\n");
            the_member_delete();
            break;
        }
        break;
    case 8:
        printf("已退出\n谢谢使用!\n");
        flags = 1; //标识符设置为1，表示退出程序
        break;
    default:
        printf("输入错误，请重新输入\n");
        break;
    }
}

void add_bicycle_information() //添加自行车信息
{
    int i;
    printf("请输入单车编号:");
    scanf("%d", &i);
    while (bicycle[i].num != 0 || i >= N || i < 0) //查找是否有重复编号
    {
        if (i == bicycle[i].num) //有重复编号
            printf("该单车编号已存在，请重新输入:");
        if (i >= N || i < 0) //超出范围
            printf("输入的数据不符，请重新输入:");
        scanf("%d", &i);
    }
    bicycle[i].num = i; //在数组的该位置添加单车编号
    printf("请输入单车所属城市:");
    scanf("%s", bicycle[i].city);
    printf("请输入单车单价(单位:万):");
    scanf("%d", &bicycle[i].price);
    printf("请输入单车骑行次数:");
    scanf("%d", &bicycle[i].riding_number);
    printf("请输入单车骑行总时长:");
    scanf("%d", &bicycle[i].total_riding_time);
    bicycle[i].sign = 'N'; //初始化单车标记
    printf("自行车信息添加成功\n");
    printf("********************\n");
}

void search_bicycle_information() //查询单车信息
{
    int i, n;
    int num_search, count = 0;
    char char_judge[20];
    printf("********************\n");
    printf("请输入查询的信息\n");
    printf("1.单车编号\n");
    printf("2.单车所属城市\n");
    printf("3.单车标记\n");
    printf("4.单车单价\n");
    printf("5.单车骑行次数\n");
    printf("6.单车骑行总时长\n");
    printf("7.返回上一级\n");
    printf("********************\n");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        printf("请输入单车编号:");
        scanf("%d", &num_search);
        if (bicycle[num_search].num == 0)
            printf("未查询到单车信息\n");
        else
            output_bicycle_information(num_search); //输出该编号的单车信息
        break;
    case 2:
        printf("请输入单车所属城市:");
        scanf("%s", char_judge);
        for (i = 1; i < N; i++)
        {
            if (strcmp(bicycle[i].city, char_judge) == 0)
                count++;
        }
        if (count == 0)
            printf("没有该城市的单车\n");
        else
            printf("属于城市%s的单车共有%d辆\n", char_judge, count);
        break;
    case 3:
        printf("请输入单车标记(Y or N):");
        scanf("%c", &char_judge[0]);
        for (i = 1; i < N; i++)
        {
            if (bicycle[i].sign == char_judge[0])
                count++;
        }
        if (count == 0)
            printf("没有单车被租借出\n");
        else
            printf("共有%d辆单车被租借出去\n", count);
        break;
    case 4:
        printf("请输入单车单价(单位:万):");
        scanf("%d", &num_search);
        for (i = 1; i < N; i++)
        {
            if (bicycle[i].price == num_search)
                count++;
        }
        if (count == 0)
            printf("没有该单价的单车\n");
        else
            printf("单价为%d万的单车共有%d辆\n", num_search, count);
        break;
    case 5:
        printf("请输入单车骑行次数:");
        scanf("%d", &num_search);
        for (i = 1; i < N; i++)
        {
            if (bicycle[i].riding_number == num_search)
                count++;
        }
        if (count == 0)
            printf("没有该次数的单车\n");
        else
            printf("骑行次数为%d的单车共有%d辆\n", num_search, count);
        break;
    case 6:
        printf("请输入单车骑行总时长:");
        scanf("%d", &num_search);
        for (i = 1; i < N; i++)
        {
            if (bicycle[i].total_riding_time == num_search)
                count++;
        }
        if (count == 0)
            printf("没有该时长的单车\n");
        else
            printf("骑行总时长为%d的单车共有%d辆\n", num_search, count);
        break;
    case 7:
        break;
    }
    printf("********************\n");
}

void output_bicycle_information(int i) //输出单车信息
{
    printf("单车编号:%d\n", bicycle[i].num);
    printf("单车所属城市:%s\n", bicycle[i].city);
    printf("单车标记:%c\n", bicycle[i].sign);
    printf("单车单价:%d\n", bicycle[i].price);
    printf("单车骑行次数:%d\n", bicycle[i].riding_number);
    printf("单车骑行总时长:%d\n", bicycle[i].total_riding_time);
}

void the_member_add() //添加会员信息
{
    int i;
    printf("********************\n");
    printf("请输入会员信息\n");
    printf("会员编号:");
    scanf("%d", &i);
    while (member[i].num != 0 || i >= N || i < 0) //数组的该位置未被占用
    {
        if (member[i].num == i) //判断会员编号是否重复
            printf("会员编号重复，请重新输入:");
        if (i >= N || i < 0) //判断会员编号是否超出范围
            printf("会员编号超出范围，请重新输入:");
        scanf("%d", &i);
    }
    member[i].num = i; //会员编号添加
    printf("会员姓名:");
    scanf("%s", member[i].name);
    printf("会员信息添加成功！\n");
    member[i].sign = 'N'; //初始化会员标记
    printf("名下现在可租借一辆单车\n");
    printf("********************\n");
}

void the_member_search() //查询会员信息
{
    int num_search, i, j, judge, count = 0;
    char name_search[20];
    printf("********************\n");
    printf("请输入查询方式:\n");
    printf("1.查询会员编号\n");
    printf("2.查询会员姓名\n");
    printf("3.返回上一级\n");
    scanf("%d", &judge);
    switch (judge)
    {
    case 1:
        printf("请输入会员编号:");
        scanf("%d", &num_search);
        while (member[num_search].num == 0 || num_search >= N || num_search < 0)
        {
            if (member[num_search].num == 0)
                printf("没有该会员，请重新输入:");
            if (num_search >= N || num_search < 0)
                printf("会员编号超出范围，请重新输入:");
            scanf("%d", &num_search);
        }
        printf("会员编号:%d\n", member[num_search].num);
        printf("会员姓名:%s\n", member[num_search].name);
        if (member[num_search].sign == 'Y')
            printf("该会员目前已租借了一辆单车\n");
        else
            printf("该会员名下目前可租借一辆单车\n");
        printf("会员信息查询成功！\n");
        break;
    case 2:
        printf("请输入会员姓名:");
        scanf("%s", name_search);
        for (i = 1; i < N; i++)
        {
            if (strcmp(name_search, member[i].name) == 0)
            {
                count++;
                j = i;
            }
        }
        if (count == 0)
            printf("没有该会员\n");
        else
        {
            printf("会员编号:%d\n", member[j].num);
            printf("会员姓名:%s\n", member[j].name);
            if (member[j].sign == 'Y')
                printf("该会员目前已租借了一辆单车\n");
            else
                printf("该会员名下目前可租借一辆单车\n");
            printf("会员信息查询成功！\n");
        }
        break;
    case 3:
        break;
    }
    printf("********************\n");
}

void the_member_delete() //删除会员信息
{
    int i;
    printf("********************\n");
    printf("请输入会员编号:");
    scanf("%d", &i);
    while (member[i].num != i || i >= N || i < 0) //数组的该位置未被占用
    {
        if (i != member[i].num) //判断会员编号是否存在
            printf("会员编号不存在，请重新输入:");
        if (i >= N || i < 0) //判断会员编号是否超出范围
            printf("会员编号超出范围，请重新输入:");
        scanf("%d", &i);
    }
    member[i].num = 0;                                 //会员编号删除
    memset(member[i].name, 0, sizeof(member[i].name)); //会员姓名删除
    member[i].sign = 'N';                              //初始化会员标记
    member[i].rent.RentTime.year = 0;                  //初始化租借时间，年
    member[i].rent.RentTime.month = 0;                 //初始化租借时间，月
    member[i].rent.RentTime.day = 0;                   //初始化租借时间，日
    member[i].rent.ReturnTime.year = 0;                //初始化归还时间，年
    member[i].rent.ReturnTime.month = 0;               //初始化归还时间，月
    member[i].rent.ReturnTime.day = 0;                 //初始化归还时间，日
    member[i].rent.theRent = 0;                        //初始化租金
    printf("会员信息删除成功！\n");
    printf("********************\n");
}

void bicycle_rent() //单车租借
{
    int i, num_search;
    printf("请输入会员编号:");
    scanf("%d", &i);
    while (member[i].num != i || i >= N || i < 0) //判断会员是否存在
    {
        if (member[i].num == 0)
            printf("会员不存在，请重新输入:");
        if (i < 0 || i > N)
            printf("数据有误，请重新输入:");
        scanf("%d", &i);
    }
    printf("欢迎会员:%s\n", member[i].name); //打印会员姓名
    if (member[i].sign == 'Y')               //判断会员是否已经租借了一辆单车
        printf("很抱歉，该会员已经租借了一辆单车\n");
    else
    {
        printf("该会员可租借一辆单车\n");
        printf("请输入单车编号:");
        scanf("%d", &num_search);
        while (bicycle[num_search].sign == 'Y' || num_search >= N || num_search < 0) //检查单车是否可租
        {
            if (num_search >= N || num_search < 0) //检查单车编号是否超出范围
                printf("该单车不存在，请重新输入:");
            if (bicycle[num_search].sign == 'Y') //单车被租出
                printf("该单车已被租借，请重新输入单车编号:");
            scanf("%d", &num_search);
        }
        printf("请输入租借时间(年月日之间请使用'/'分隔):");
        scanf("%d/%d/%d", &member[i].rent.RentTime.year, &member[i].rent.RentTime.month, &member[i].rent.RentTime.day);
        bicycle[num_search].sign = 'Y'; //单车被租出，修改单车标记
        member[i].sign = 'Y';           //会员标记也改为已租借
        printf("您已租借成功！\n");
    }
    printf("********************\n");
}

void bicycle_return() //单车归还
{
    int i, num_search, days;
    printf("请输入会员编号:");
    scanf("%d", &i);
    while (member[i].num != i || i >= N || i < 0) //判断会员是否存在
    {
        if (member[i].num == 0)
            printf("会员不存在，请重新输入:");
        if (i < 0 || i > N)
            printf("数据有误，请重新输入:");
        scanf("%d", &i);
    }
    printf("欢迎会员:%s\n", member[i].name);
    if (member[i].sign == 'N') //判断会员是否已经租借了一辆单车
        printf("很抱歉，该会员没有租借单车\n");
    else
    {
        printf("请输入单车编号:");
        scanf("%d", &num_search);
        while (bicycle[num_search].sign == 'N' || num_search >= N || num_search < 0) //检查单车是否被租出
        {
            if (num_search >= N || num_search < 0) //检查单车编号是否超出范围
                printf("该单车不存在，请重新输入:");
            if (bicycle[num_search].sign == 'N') //单车未被租出
                printf("该单车未被租出，请重新输入单车编号:");
            scanf("%d", &num_search);
        }
        printf("请输入归还时间(年月日之间请使用'/'分隔):");
        scanf("%d/%d/%d", &member[i].rent.ReturnTime.year, &member[i].rent.ReturnTime.month, &member[i].rent.ReturnTime.day);
        days = days_between(member[i].rent.RentTime, member[i].rent.ReturnTime); //计算租借天数
        while (days <= 0)
        {
            printf("归还时间不能早于租借时间，请重新输入归还时间:");
            scanf("%d/%d/%d", &member[i].rent.ReturnTime.year, &member[i].rent.ReturnTime.month, &member[i].rent.ReturnTime.day);
            days = days_between(member[i].rent.RentTime, member[i].rent.ReturnTime); //再次计算租借天数
        }
        printf("租借天数为%d天\n", days);
        bicycle[num_search].sign = 'N';                             //单车被归还，修改单车标记
        member[i].sign = 'N';                                       //会员标记也改为未租借
        member[i].rent.theRent += days * bicycle[num_search].price; //计算租借费用，租借天数*单车价格
        printf("您已归还成功！\n");
        printf("本次租借费用为:%d\n", member[i].rent.theRent);
    }
}

int days_between(Date date1, Date date2) //计算两个日期之间相差的天数
{
    int days = 0, i;
    if (date1.year > date2.year) //判断年份大小
        return 0;
    else
    {
        if (date1.month > date2.month) //判断月份大小
            return 0;
        else
        {
            if (date1.day > date2.day) //判断天数大小
                return 0;
            else
            {
                for (i = date1.year; i < date2.year; i++) //计算年份天数
                {
                    if ((i + 1) % 4 == 0 && (i + 1) % 100 != 0 || (i + 1) % 400 == 0) //累加的是上一年，所以下一年是闰年的话需要加1
                        days += 366;
                    else
                        days += 365;
                }
                for (i = date1.month; i < date2.month; i++) //计算月份天数
                {
                    if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
                        days += 31;
                    else if (i == 4 || i == 6 || i == 9 || i == 11)
                        days += 30;
                    else if (i == 2)
                        days += 28;
                }
                days += (date2.day - date1.day); //再加上日期天数
                return days;
            }
        }
    }
}

void bicycle_Scrap() //单车报废
{
    int i, num_search;
    printf("请输入单车编号:");
    scanf("%d", &num_search);
    while (bicycle[num_search].sign == 'Y' || num_search >= N || num_search < 0) //检查单车是否被租出
    {
        if (num_search >= N || num_search < 0) //检查单车编号是否超出范围
            printf("该单车不存在，请重新输入:");
        if (bicycle[num_search].sign == 'Y') //单车正被租出
            printf("该单车正被租出，请重新输入单车编号:");
        scanf("%d", &num_search);
    }
    printf("********************\n");
    printf("您确定要报废该单车吗？\n");
    printf("请输入1确认报废，输入0取消报废:");
    printf("********************\n");
    scanf("%d", &i);
    if (i == 1)
    {
        bicycle[num_search].num = 0;                                           //单车被报废，该位置的单车全部数据被清空
        memset(bicycle[num_search].city, 0, sizeof(bicycle[num_search].city)); //清空单车城市数据
        bicycle[num_search].sign = 'N';                                        //单车标记被清空
        bicycle[num_search].price = 0;                                         //单车单价被清空
        bicycle[num_search].riding_number = 0;                                 //单车行驶里程被清空
        bicycle[num_search].total_riding_time = 0;                             //单车行驶里程被清空
        printf("您已报废成功！\n");
    }
    else
        printf("您已取消报废！\n");
    printf("已返回主页\n");
}

void statistical() //统计功能
{
    int i, member_count = 0, rent_count = 0;
    for (i = 1; i < N; i++) //计算会员数量
    {
        if (member[i].num != 0)
            member_count++;
    }
    printf("目前共有%d位会员\n", member_count);
    for (i = 1; i < N; i++) //计算目前已租借出的单车数量
    {
        if (member[i].sign == 'Y')
            rent_count++;
    }
    printf("目前共有%d位会员正在租车\n", rent_count);
    printf("谢谢使用\n");
}
