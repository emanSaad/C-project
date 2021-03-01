#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<locale.h>
#include<string.h>
#define SIZE 100

typedef struct clothes
{
    int code;
    char brand[20];
    char name[20];
    int size;
    float price;
    int qta_stock;
    int qta_min_stock;

} CLOTHES;

void write_file(CLOTHES *s, int n)
{
    int i;
    FILE *fClose;
    fClose = fopen("clothData.txt", "w");
    for (i = 0; i < n; i++)
        fprintf(fClose, "%d %s %s %d %.2f %d %d\n", s[i].code, s[i].brand, s[i].name, s[i].size, s[i].price, s[i].qta_stock, s[i].qta_min_stock);
    fclose(fClose);
    printf("The data has been written to the file.\n");
}

void enter_product(CLOTHES *x, int *dim)
{
    int n;
    printf("How many products do you need to insert?\n");
    scanf("%d", &n);
    int ult_cog = x[*dim - 1].code;
    for (int i = 0; i < n; i++)
    {
        x[i].code = ult_cog++;

        printf("What is the brand of product %d:", i + 1);
        scanf("%s", x[i].brand);
        printf("What is the name of product %d:", i + 1);
        scanf("%s", x[i].name);
        printf("What is the size of product %d:", i + 1);
        scanf("%d", &x[i].size);
        printf("What is the price of product %d:", i + 1);
        scanf("%f", &x[i].price);
        printf("What is the quantity in the store of product %d:", i + 1);
        scanf("%d", &x[i].qta_stock);
        printf("What is the minimum quantity of prodcut %d:", i + 1);
        scanf("%d", &x[i].qta_min_stock);
    }
    *dim = *dim + n;
}

int read_file(CLOTHES sp[100])
{
    FILE *fRead;
    int i = 0, cod;
    int code;
    char brand[20];
    char name[20];
    int size;
    float price;
    int qta_stock;
    int qta_min_stock;

    if ((fRead = fopen("clothData.txt", "r")) == NULL)
    {
        printf("File does not exist!!\n");
        exit(1);
    }
    while (fscanf(fRead,"%d %s %s %d %f %d %d", &code, brand, name, &size, &price, &qta_stock, &qta_min_stock) != EOF)
    {
         printf("%d *** %s *** %s *** %d *** %f *** %d *** %d\n", code, brand, name, size, price, qta_stock, qta_min_stock);
         sp[i].code=code;
         strcpy(sp[i].brand,brand);
         strcpy(sp[i].name,name);
        
         sp[i].size=size;
         sp[i].price=price;
         sp[i].qta_stock=qta_stock; 
         sp[i].qta_min_stock=qta_min_stock;
        i++;
    }
 //printf("ERRO2\n");
    fclose(fRead);
    return i;
}
void showProducts(CLOTHES x[100], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Code: %d\n", x[i].code);
        printf("brand: %s\n", x[i].brand);
        printf("Name: %s\n", x[i].name);
        printf("Size: %d\n", x[i].size);
        printf("Price: %f\n", x[i].price);
        printf("Quantity in the store: %d\n", x[i].qta_stock);
        printf("Minimum quantity in the store : %d\n", x[i].qta_min_stock);
    }
}

//search by code or name
int search_by_code_or_name(CLOTHES sp[100], int dim)
{
    char name[20];
    int res;
    int cod_int, pos=-1, option;
    bool found = false;
    printf("enter your option:\n press 1 to search by code or press 2 to search by name:");
    scanf("%d", &option);
    if (option == 1)
    {
        printf("Enter the code of the product:\n");
        scanf("%d", &cod_int);
        for (int i = 0; i < dim; i++)
            if (cod_int == sp[i].code)
            {
                pos = i;
                found = true;
                break;
            }

        if (found == false)
            printf("\n\nThis code does not exist... Please insert a correct code\n\n");
            //printf("postion%d",pos);
        return pos;
    }

    if (option == 2)
    {
        printf("Enter the name of the product: ");
        scanf("%s", name);
        for (int i = 0; i < dim; i++)
        {
            res = strcmp(sp[i].name, name);
            if (res == 0)
            {
                pos = i;
                found = true;
                break;
            }
        }
        if (found == false)
            printf("\n\nThis name does not exist... Please insert a valid name\n\n");
        return pos;
    }
}

void checkInNewQuant(CLOTHES sp[100], int dim)
{
    int newQut;
    int i = search_by_code_or_name(sp, dim);
    if (i >= 0)
    {
        printf("Enter the new quantity: ");
        scanf("%d", &newQut);
        sp[i].qta_stock = sp[i].qta_stock + newQut;
        printf("The new quantity of product has been added.");
    }
}
void checkOutQuant(CLOTHES sp[100], int dim)
{
    int soldQut;
    int i = search_by_code_or_name(sp, dim);

    printf("Enter the sold quantity: ");
    scanf("%d", &soldQut);
    if (sp[i].qta_stock > soldQut)
    {
        sp[i].qta_stock = sp[i].qta_stock - soldQut;
        if (sp[i].qta_stock > sp[i].qta_min_stock)
            printf("The checkout performed successfuly ");
        else
            printf("\n\n This Product reach the minimum quantity and should be ordered: %d \n", sp[i].qta_min_stock);
    }
    else
        printf("\n\nSorry we do not have this quantity in our store. \n");
}

void showOneProduct(CLOTHES sp[100], int dim)
{
    int i = search_by_code_or_name(sp, dim);
    if (i >= 0)
    {
        printf("Code: %d\n", sp[i].code);
        printf("Brand: %s\n", sp[i].brand);
        printf("Name: %s\n", sp[i].name);
        printf("Size: %d\n", sp[i].size);
        printf("Price: %f\n", sp[i].price);
        printf("Quantity in the store: %d\n", sp[i].qta_stock);
        printf("Minimum quantity in the store: %d\n", sp[i].qta_min_stock);
    }
}

void showBrandInfo(CLOTHES sp[100], int dim)
{
    char brand[20];
    int res;
    bool here = false;
    printf("Enter the brand of clothes: ");
    scanf("%s", brand);
    for (int i = 0; i < dim; i++)
    {
        res = strcmp(sp[i].brand, brand);
        if (res == 0)
        {
            here = true;
            printf("Code: %d\n", sp[i].code);
            printf("Name: %s\n", sp[i].name);
            printf("Size: %d\n", sp[i].size);
            
        }
    }
    if (here == false)
        printf("\n\nERROR, This brand doen't exist, please enter a valid brand\n\n");
}

void changeProductInfo(CLOTHES sp[100], int dim)
{
    int i = search_by_code_or_name(sp, dim);
    if (i >= 0)
    {
        printf("What is the brand of the product:");
        scanf("%s", sp[i].brand);
        printf("What is the name of the product:");
        scanf("%s", sp[i].name);
        printf("What is the size of the product:");
        scanf("%d", &sp[i].size);
        printf("What is the price of the product:");
        scanf("%f", &sp[i].price);
        printf("What is the quantity in the store:");
        scanf("%d", &sp[i].qta_stock);
        printf("What is the minimum quantity in the store:");
        scanf("%d", &sp[i].qta_min_stock);
        printf("\n\nThe product data is updated successfully....\n\n");
    }
}

void deleteOneProduct(CLOTHES sp[100], int dim)
{
    int code;
    bool here = false;
     int pos = search_by_code_or_name(sp, dim);
    if (pos >= 0)
    {
         for (int j = pos; j < dim; j++)
                sp[j] = sp[j + 1];
                 dim=dim-1;
    }
}

void checkProdToOrder(CLOTHES sp[100], int dim)
{    
    int count=0;

    for (int i = 0; i < dim; i++)
    {
        if (sp[i].qta_stock <= sp[i].qta_min_stock)
        { count++;
            printf("This product need to be ordered: %d \n", sp[i].code);
            printf("its quantity in stock is: %d\n", sp[i].qta_stock);
            printf("its minimum quantity is: %d\n", sp[i].qta_min_stock);
        }
    }
    if (count==0)
    {
        printf("\nAll products do not reach the minimum quantity, no need to order!!\n\n");
    }
    
}

void menu(CLOTHES sp[100])
{
    int option;
    int n;
    int dim = 0;
    dim = read_file(sp);
   // printf("number of producct is: %d\n", dim);
    do
    {
        printf("Enter your option: ");
        printf("\n Enter 1 to indroduce a new product.\n");
        printf("Enter 2 to check in a new quantity of a product.\n ");
        printf("Enter 3 to check out a certain quantity of a product.\n ");
        printf("Enter 4 to list all products in the store.\n");
        printf("Enter 5 to list the information of certain product.\n");
        printf("Enter 6 to list info about a certain brand.\n");
        printf("Enter 7 to change product information.\n");
        printf("Enter 8 to delete a product.\n");
        printf("Enter 9 to list the products to be ordered.\n");
        printf("Enter 10 to exit.\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            enter_product(sp, &dim);
            break;
        case 2:
            checkInNewQuant(sp, dim);
            break;
        case 3:
            checkOutQuant(sp, dim);
            break;
        case 4:
            showProducts(sp, dim);
            break;
        case 5:
            showOneProduct(sp, dim);
            break;
        case 6:
            showBrandInfo(sp, dim);
            break;
        case 7:
            changeProductInfo(sp, dim);
            break;
        case 8:
            deleteOneProduct(sp, dim);
            break;
        case 9:
            checkProdToOrder(sp, dim);
            break;
        case 10:
            printf("Thank you, everything will be written to the file..\n\n");
            write_file(sp, dim);
            exit(0);
        }
    } while (option != 10);
}

int main()
{
    CLOTHES s[100];
    menu(s);

    return 0;
}