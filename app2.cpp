/* 
    addition of univariant polynomial ( power descending)
    eg: p(x) =  9 x^8  +  3 x^2 + 7 
        q(x) =  10 x^5 +  3 x   + 2
    implementation: variant of linked list
    ! seqlist may give rise to sparseness issue
    ! problem of merging of two sorted list involved:  O(m+n) -> DP
*/


#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif

#define MAX(x,y) ( (x>y)?x:y )

typedef struct _Term
{
    int coef;
    int exp;
} Term;

bool operator==(const Term &A, const Term &B)
{
    return (A.coef == B.coef) && (A.exp == B.exp);
}

bool operator!=(const Term &A, const Term &B)
{
    return ( (A.coef != B.coef) || (A.exp != B.exp) ) ;
}

template <class elemType>
struct Node
{
    elemType data;
    Node *next;
    Node(const elemType &x, Node *n = NULL)
        {data = x; next = n;}
    Node(void): next(NULL){}
    ~Node(){}
};

template <class elemType>
class Polynomial
{
    private:
        Node<elemType> *head;
        elemType stop_flag; // stop flag of polynomial
    public:
        // get assigned stop-flag from user
        Polynomial(const elemType &stop);
        void getPoly(int n);
        void addPoly(const Polynomial &L1, const Polynomial &L2);//outer L1 + L2 -> this
        void dispPloy(void) const; //print itself
        void clear(void); //clear the data
        ~Polynomial(void){clear(); delete head;}

};

template <class elemType>
Polynomial <elemType>:: Polynomial(const elemType &stop)
{
    stop_flag = stop;
    head = new Node<elemType> ();
}


template <class elemType>
void Polynomial <elemType>:: getPoly(int n)
{
    int count=0;
    Node<elemType> *tmp, *p;
    p = head;

    //cout << "start your enter: " << endl;

    while(1)
    {
        tmp = new Node<elemType> ();
        cin >> (tmp->data).coef >> (tmp->data).exp;
        p->next = tmp; p = p->next;
        count++;
        if (count == n)
            break;
       
    }

    tmp = new Node<elemType> ();
    tmp->data = stop_flag;
    p->next = tmp; p = p->next;
    //printf("###%d### %d####\n",(p->data).coef,(p->data).exp);

}


/*
addition: 3 case for current power compare
1. power_a = power_b
2. power_a < power_b
3. power_a > power_b

so we need sequentially create new node for C and push the maxima's copy into the rear
*/

template <class elemType>
void Polynomial <elemType>:: addPoly(const Polynomial &L1, const Polynomial &L2)
{
    Node<elemType> *p1, *p2, *tmp, *p;
    p = head;
    int maxOrder, currentOrder = -2;
    p1 = (L1.head)->next;
    p2 = (L2.head)->next;

    while((p1->data != stop_flag) || (p2->data != stop_flag))
    {
        
        if((p1->data).exp == currentOrder)
        {
            (p->data).coef += (p1->data).coef;
            p1 = p1->next;
            continue;
        }
        if((p2->data).exp == currentOrder)
        {
            (p->data).coef += (p2->data).coef;
            p2 = p2->next;
            continue;
        }
        
        //next node
        maxOrder = MAX( (p1->data).exp, (p2->data).exp);
        tmp = new Node<elemType> ();
        (tmp->data).coef = 0;

        
        if((p1->data).exp == maxOrder)
        {
            (tmp->data).coef += (p1->data).coef;
            (tmp->data).exp = (p1->data).exp;
            p1 = p1->next;
        }

        if((p2->data).exp == maxOrder)
        {
            (tmp->data).coef += (p2->data).coef;
            (tmp->data).exp = (p2->data).exp;
            p2 = p2->next;
        }
        //if cancel the coefficient, then continue;
        if( (tmp->data).coef == 0)
        {
            currentOrder = (tmp->data).exp;
            continue;
        }
        p->next = tmp; p = p->next; currentOrder = (p->data).exp;
    }
    // end of polynomial
    tmp = new Node<elemType>();
    tmp->data = stop_flag;
    p->next = tmp;
    return;
}


template <class elemType>
void Polynomial <elemType>:: dispPloy(void) const
{
    Node<elemType> *p = head;
    p = p->next;
    // first check

    if(p->data == stop_flag)
    {
        return;
    }
    
    if((p->data).exp == 0)
        {
            if((p->data).coef >= 0)
                cout << (p->data).coef;   
            else if((p->data).coef < 0)
                cout << "- "<< -(p->data).coef;
            return;
        }
        else if((p->data).exp == 1)
        {
            if((p->data).coef > 1)
                cout << (p->data).coef << 'x';
            else if((p->data).coef == 1)
                cout << 'x';
            else if((p->data).coef == -1)
                cout << "- " << 'x' << '^' << (p->data).exp;    
            else if((p->data).coef < 0)
                cout << "- " << -(p->data).coef << 'x';
        }
        else
        {
            if((p->data).coef > 1)
                cout << (p->data).coef << 'x' << '^' << (p->data).exp;
            else if((p->data).coef == 1)
                cout << 'x' << '^' << (p->data).exp;
            else if((p->data).coef == -1)
                cout << "- " << 'x' << '^' << (p->data).exp;    
            else if((p->data).coef < 0)
                cout << "- " << -(p->data).coef << 'x' << '^' << (p->data).exp;
        }

    // traverse the rest of the polynomial
    p = p->next;
    while(p->data != stop_flag)
    {
        cout << ' ';// split
        if((p->data).exp == 0)
        {
            if((p->data).coef >= 0)
                cout << "+ " << (p->data).coef;   
            else if((p->data).coef < 0)
                cout << "- "<< -(p->data).coef;
            return;
        }
        
        else if((p->data).exp == 1)
        {
            if((p->data).coef > 1)
                cout << "+ " << (p->data).coef << 'x';
            else if((p->data).coef == 1)
                cout << "+ " << 'x';
            else if((p->data).coef == -1)
                cout << "- " << 'x' << '^' << (p->data).exp;        
            else
                cout << "- " << -(p->data).coef << 'x';
            p = p->next;
        }
        else
        {
            if((p->data).coef > 1)
                cout << "+ " << (p->data).coef << 'x' << '^' << (p->data).exp;
            else if((p->data).coef == 1)
                cout << "+ " << 'x' << '^' << (p->data).exp;    
            else if((p->data).coef == -1)
                cout << "- " << 'x' << '^' << (p->data).exp; 
            else
                cout << "- " << -(p->data).coef << 'x' << '^' << (p->data).exp;
            p = p->next;
        }
    }
}


template <class elemType>
void Polynomial <elemType>:: clear(void)
{
    Node<elemType> *p = head->next;
    Node<elemType> *tmp;

    head->next = NULL;
    while(p)
    {
        tmp = p;
        p = p->next;
        delete tmp;
    }
}

// general function to get flag from user input
void getStop(Term &flag)
{
    cout << "Please input the <coefficient, exponential> of self-defined stop flag of polynomial"<<endl;
    cin >> flag.coef >> flag.exp;
    cout << "Accepted input as < "<<flag.coef << ',' << flag.exp << ">" << endl;
}

int main(void)
{
    int m,n;
    Term stop_flag;
    //getStop(stop_flag);
    /* here we auto type in the stop flag as [0,-1] */
    stop_flag.coef = 0;
    stop_flag.exp = -1;

    Polynomial<Term> L1(stop_flag), L2(stop_flag), L3(stop_flag);

    cin >> m >> n;
    L1.getPoly(m);
    L2.getPoly(n);


    L3.addPoly(L1,L2);
    L3.dispPloy();

    return 0;
}