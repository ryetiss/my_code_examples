#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct nodeList
{
	char ID[3];		//Öğrenci Numarası Listesi ilk düğümünde bu değer son 3 hane olarak ayarlanıp diğer düğümlerde boş bırakılacak
    int data; 		//Öğrenci Numarası Listesi ilk düğümünde bu değer -1 olarak ayarlanıp diğer düğümlerde sırayla ayarlanacak
    struct nodeList *rear;
};                   //Öğrenci Numaralarını saklayacak Listenin Düğüm Yapısı
struct nodeList *front=NULL;    


struct nodeStack
{
	char ID[3];				//Her bir yığın değeri için son 3 hane olarak ayarlanacak (liste düğümünün ID'si ile aynı olacak)
   	struct nodeList *front;	//Her bir yığın değeri için öğrenci numarası listesinin ilk düğümü olarak ayarlanacak
    struct nodeStack *next;   
};					//Öğrenci Numaralarını içeren listelerin saklancağı yığın yapısı

struct nodeStack *first;    



void Insert(int tmpData);   //Öğrenci numarası listesine düğüm ekleyen yöntem, InsertNumberToList yönteminde numaralar parçalanarak bu yöntem ile listeye eklenecek
void InsertNumberToList();	//Öğrenci numarası girdisi alarak liste haline getirecek ve yığına iletecek yöntem
void PrintNumberList(struct nodeList *firstNode);	//Öğrenci listesinin düğümlerini yazdıran yöntem, aşağıdaki yığın yazdırma yönteminde her bir yığın öğesinde bulunan liste ilk düğümü için bu yöntem çağrılacak

void pushToStack();	//Öğrenci listesini yığına ekleyen yöntem
void printStack();	//Yığındaki bilgileri yazdıran yöntem

void findMinimum();

int main()
{
    int choice;
    
    do
    {
    	printf("\n***\n1.Numara Ekle\n2.Tum Numaralari Yazdir\n3.En Kucuk Numarayi Bul\n4.Cikis\n");
        printf("\nSeciminiz : ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
                InsertNumberToList();
                break;
        case 2:
                printStack();
                break;
        case 3:
                findMinimum();
                break;
		case 4: printf("\nCikiliyor...");
				break;
        default: printf("Hatali Secim!");
        }
    }while(choice!=4);
    return 0;
}


void Insert(int tmpData)
{
    
        struct nodeList *ptr,*cpt;
        ptr=front;
        
        while(ptr->rear!=NULL)	//Listenin sonuna gidiliyor
        {
            ptr=ptr->rear;
        }
        
        cpt=(struct nodeList *)malloc(sizeof(struct nodeList));
		cpt->data=tmpData;
        cpt->rear=NULL;
        
		ptr->rear=cpt;	//Listenin sonuna düğüm eklendi
    
}

void InsertNumberToList()
{
	
	char *ch;
	printf("Ogrenci numarasi giriniz : ");
	scanf("%s",ch);
	
	int  length= strlen(ch);
	
	if(length!=9){
    	
    	printf("Ogrenci numarasi 9 hane olmali\n",strlen(ch));
	}
	else{
	
		int i;
	    for(i=-1;i<length;i++){  //Öğrenci numarasından tek tek rakamları alıp listeye ekleyen döngü
		
			if(i==-1){	//Listenin ilk düğümü numaranın son 3 hanesini içereceği için döngü -1 den başlatılıyor ve liste nin ilk düğümü ID bilgisini içerecek şekilde ayarlanıyor
				struct nodeList *ptr;
        		ptr=(struct nodeList *)malloc(sizeof(struct nodeList));
        		ptr->data = -1;            
				strncpy(ptr->ID,ch+6, 3); //Son 3 hane ID değerine ayarlanıyor
        		ptr->rear=NULL;
        		front=ptr;
			}
			else{
				
				Insert(ch[i]- 48);	// Öğrenci numarasını karakter dizisi olarak aldığımız için her bir karakterden 0'ın ASCII değeri olan 48 i çıkararak girilen rakamın ondalık değerini buluyoruz
				
			}
			
		}
		
		pushToStack(front);
	
	}

}





void PrintNumberList(struct nodeList *firstNode)
{
    if(firstNode==NULL)
    {
        printf("Hata! Numara Listesi Boş...");
    }
    else
    {
        struct nodeList *ptr;
        ptr=firstNode;
        while(ptr!=NULL)	//Döngü ile listenin başından sonuna gidiliyor ve her döngü için değerler yazdırılıyor
        {
            if(ptr->data==-1)	//İlk düğüm ID değerini içereceği için data değerini -1 atamıştık bunu kontrol ederek ID değerini yazdırıyoruz
        		printf("Liste ID'si': %s\n",ptr->ID);
        	else
            	printf("  %d\t",ptr->data);
            ptr=ptr->rear;
        }
    }
}




void pushToStack(struct nodeList *tmpListNode)
{
    if(first==NULL)		//Yığın boş ise ilk çğe oluşturuluyor
    {
            struct nodeStack *ptr;
            ptr=(struct nodeStack *)malloc(sizeof(struct nodeStack));
            
            ptr->ID[0] = tmpListNode->ID[0];	
            ptr->ID[1] = tmpListNode->ID[1];
            ptr->ID[2] = tmpListNode->ID[2];
            ptr->front=tmpListNode;
            
            ptr->next=NULL;
            first=ptr;
    }
    else
    {
        struct nodeStack *ptr,*cpt;
        ptr=first;
        cpt=(struct nodeStack *)malloc(sizeof(struct nodeStack));
      
      	cpt->ID[0] = tmpListNode->ID[0];	//Yığın yapısındaki ID değeri, öğrenci numarası listesinin ID değerine eşitleniyor
        cpt->ID[1] = tmpListNode->ID[1];
        cpt->ID[2] = tmpListNode->ID[2];
		cpt->front=tmpListNode;				//Yığın yapısındaki öğrenci numarası listesinin ilk düğümü ayarlanıyor
      
        cpt->next=ptr;
        ptr=cpt;
        first=ptr;
    }
}



void printStack()
{
    struct nodeStack *ptr;
    ptr=first;
    if(ptr==NULL)
    {
        printf("\nYigin Bos\n");
    }
    else
    {
        printf("\nYigindaki Veriler\n");
        printf("*****************\n");
        while(ptr!=NULL)		//Yığındaki baştan sona gidilirek her bir yığın öğesinin ID değeri yazdırıldıktan sonra Liste ilk düğümü PrintNumberList yöntemine gönderilerek liste yazdırılıyor
        {
        	printf("---------\n");
        	printf("Yigin ID'si':%s\n",ptr->ID);
        	PrintNumberList(ptr->front);
            ptr=ptr->next;
            printf("\n---------\n");
        }
        printf("*****************\n");
    }
}

void findMinimum(){
	
	struct nodeList *minNode;
	int minID=1000; //Son üç basamağa bakacağımız için en büyüğü 999 olabileceği için ilk atama yapılıyor
	
	struct nodeStack *ptr;
    ptr=first;
    if(ptr==NULL)
    {
        printf("\nYigin Bos\n");
    }
    else
    {
        while(ptr!=NULL)
        {
        	if(atoi(ptr->ID)<minID){		//Yığında baştan sona öğeler kontrol ediliyor. ID degeri son 3 basamağı içerdiği için karşılaştırılıyor ve düşük ID'ye sahip öğe en küçük olarak alınıyor
        		minID = atoi(ptr->ID);
        		minNode = ptr->front;
			}
            ptr=ptr->next;
        }
        
        printf("*****************\nSon 3 basama gore en kucuk numara:\n");
        PrintNumberList(minNode);		//Bulunan en küçük öğenin liste ilk düğümü yardımıyla en küçük öğrenci numarası yazdırılıyor
        printf("\n*****************\n");
    }
}
