#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <map>
#include <bits/stdc++.h>
using namespace std;

// HUFFMAN COMPRESSION FOR TEXT

#define max_tree_huffman 50

// Creating a Huffman tree node with frequency of the item
struct MinNode {
    unsigned freq;
    char item;
    struct MinNode *left, *right;
};

// Creating a minimum heap of a given capacity
struct MinH {
    unsigned size;
    unsigned capacity;
    struct MinNode **array;
};

// Creating a single Huffman tree node
struct MinNode *newNode(char item, unsigned freq) {
    struct MinNode *temp = (struct MinNode *)malloc(sizeof(struct MinNode));

    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;

    return temp;
}

// Creating a minimum heap using given capacity
struct MinH *createMinH(unsigned capacity) {
    struct MinH *minHeap = (struct MinH *)malloc(sizeof(struct MinH));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinNode **)malloc(minHeap->capacity * sizeof(struct MinNode *));
    return minHeap;
}

// Print the array
void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        cout << arr[i];
    cout << "\n";
}

// Swap function
void swapMinHNode(struct MinNode **a, struct MinNode **b) {
    struct MinNode *t = *a;         // using a temporary node t to swap nodes a and b
    *a = *b;
    *b = t;
}

// Heapify
void minHeapify(struct MinH *minHeap, int k) {
    int smallest = k;
    int left = 2 * k + 1;
    int right = 2 * k + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != k) {
        swapMinHNode(&minHeap->array[smallest], &minHeap->array[k]);
        minHeapify(minHeap, smallest);
    }
}

// Check if size of heap is 1
int checkSizeOne(struct MinH *minHeap) {
    return (minHeap->size == 1);
}

// Extract the minimum heap
struct MinNode *extractMin(struct MinH *minHeap) {
    struct MinNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// Insertion of a node into minimum heap
void insertMinHeap(struct MinH *minHeap, struct MinNode *minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// Build a minimum heap
void buildMinHeap(struct MinH *minHeap) {
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Checks if the node is a leaf or not
int isLeaf(struct MinNode *root) {
    return !(root->left) && !(root->right);
}

// Creates and builds a minimum heap 
struct MinH *createAndBuildMinHeap(char item[], int freq[], int size) {
    struct MinH *minHeap = createMinH(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(item[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// Builds Huffman tree by taking elements, thier frequencies, and size of the array as inputs
struct MinNode *buildHuffmanTree(char item[], int freq[], int size) {
    struct MinNode *left, *right, *top;
    struct MinH *minHeap = createAndBuildMinHeap(item, freq, size);

    while (!checkSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Prints Huffman codes for the individual characters
void printHuffmanCodes(struct MinNode *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printHuffmanCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printHuffmanCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        cout << root->item << "  | ";
        printArray(arr, top);
    }
}

// Wrapper function
void HuffmanCodes(char item[], int freq[], int size) {
    struct MinNode *root = buildHuffmanTree(item, freq, size);

    int arr[max_tree_huffman], top = 0;

    printHuffmanCodes(root, arr, top);
}






//HUFFMAN COMPRESSION FOR IMAGES

int bit_counter;
char current_byte='\0';
int n;
FILE* compressedFile;

class pixel     // class specifying specs for a single pixel
{
public:
    int r;
    int g;
    int b;
    int hex;
    vector<int> bitcode;
    int getHex()
    {
        return hex;
    }
    void setHex(int val)
    {
        if(hex>0)
        {
            hex=val;
        }
    }
    pixel()     //constructor
    {
        r=0;
        g=0;
        b=0;
        hex=0;
    }
    void   createPixel(int a,int b,int c)       //creates pixel with given values of RGB
    {
        r=a;
        g=b;
        b=c;
        hex=calculateRGB(r,g,b);
    }
    int calculateRGB(int r, int g, int b)       //calculates hexcode by RGB values
    {
        return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
    }
};

class color         // class specifying color specs
{
   public:
    int hex;
    int frequency;
    vector<int> bit;
    color * left,* right;
    color()     //constructor
    {
        hex=0;
        frequency=0;
    }

    void setFrequency(int hexcode, int freq)        // sets frequency and hexcode of a color
    {
        hex = hexcode;
        frequency = freq;
    }

    int getHex()
    {
        return hex;
    }

    int getFreq()
    {
        return frequency;
    }
}arr[100];

struct imageInfo        // struct with image specifications
{
    int width;
    int height;
    int sizeim;
    pixel imageMatrix[500];
};

imageInfo readBMP()
{
    char filename[]="Test2.bmp";
    FILE* f = fopen(filename, "r");
    int bmpHeader[54];
    imageInfo bmp;
    for(int i=0;i<54;i++)
    {
        bmpHeader[i]=getc(f);
    }
    bmp.width = *(int*)&bmpHeader[18];
    bmp.height = *(int*)&bmpHeader[22];
    bmp.sizeim = 3 *bmp. width *bmp. height;
    int count=0;
    int r=0;
    int g=0;
    int b=0;
    for(int i=0;i<bmp.sizeim/3;i++)
    {
        b=getc(f);

        g=getc(f);

        r=getc(f);

        bmp.imageMatrix[i].createPixel(r,g,b);

        count++;
    }
    return bmp;
}

void initCompressedFile()       // initialising a compressed file 
{
    int numberOfColors;
    compressedFile = fopen("Test2.cmpbmp","a");
    current_byte='\0';
}


bool comparePixel(pixel p1, pixel p2)       // comparing pixels
{
    return p1.getHex() < p2.getHex();
}

bool compareFreq(color f1, color f2)        // comparing frequencies
{
    return f1.getFreq() < f2.getFreq();
}

int getFrequency(imageInfo info, int n, unordered_map<int, int> &freq)      // get frequency map size ,i.e, frequency
{
    int low = 0, high = n-1, i = 0;

    while(low <= high)
    {
        if(info.imageMatrix[low].getHex() == info.imageMatrix[high].getHex())
        {
            freq[info.imageMatrix[low].getHex()] += high - low + 1;
            low = high + 1;
            high = n-1;
        }
        else
            high = (low + high)/2;
    }

    return freq.size();
}
struct compare      // compare color a and color b
{
    bool operator()(color * a,color * b)
    {
        return(b->frequency < a->frequency);
    }

};
color * makenode(int hex, int frequency)        // make new node for a color using hexcode and its frequency
{
    color * temp = new color;
    temp->hex = hex;
    temp->frequency = frequency;
    temp->left = temp->right = NULL;
    return temp;
}
void generatecode(color * root,int code[],int index = 0)        // generate hexcode for the node 
{
    if(root->left)
    {
        code[index] = 0;
        generatecode(root->left,code,index + 1);
    }
    if(root->right)
    {
        code[index] = 1;
        generatecode(root->right,code,index + 1);
    }
    if(!root->left && !root->right)
    {

        int j = 0;
        for(int i = index - 1;i >= 0;--i)
        {
            root->bit.insert(root->bit.begin(),code[i]);
        }

        for(int i=0;i<n;i++)
        {
            if(arr[i].getHex() == root->getHex())
                arr[i].bit = root->bit;
        }
    }
}

void huffmancode(color *arr,int size)        // converting the node to its Huffman bitcode
{
    color* temp1;
    list<color *>compressedList;
    int colour[size],freq[size];
    for(int i = 0;i < size;++i)
    {
        temp1 = arr+i;
        colour[i] = temp1->getHex();
        freq[i] = temp1->getFreq();
    }
    int code[16];
    color * left, * right;
    priority_queue<color *,vector<color *>,compare>pq;
    for(int i = 0;i < size;++i)
    {
        pq.push(makenode(colour[i],freq[i]));
    }
    while(pq.size() != 1)
    {
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();
        color * temp = makenode('#',left->frequency + right->frequency);
        temp->left = left;
        temp->right = right;
        pq.push(temp);
    }
    generatecode(pq.top(),code);
}

void writeBitToFile(int a,FILE *f )     // writes individual bits to the file
{
    char current_bit = (char)a;
    bit_counter++;
    current_byte=current_byte<<1;
    current_byte=current_byte | current_bit;
    if(bit_counter==8)
    {
        fwrite(&current_byte,1,1,f);
        bit_counter=0;
        current_byte='\0';
    }
}

void writeHeader()      // writes header to the file
{
    FILE* header = fopen("Test2.cmpbmp","w");
    fwrite(&n,sizeof(int),1,header);
    for(int i=0;i<n;i++)
    {
        fwrite(&arr[i].hex,sizeof(int),1,header);
        fwrite(&arr[i].frequency,sizeof(int),1,header);
    }
    fclose(header);
}




int main() {
    cout << "Enter type of input (TEXT or IMAGE): ";
    string ans;
    cin >> ans;
    if(ans=="TEXT") {
        string input;
        cout << "Enter input string: ";
        cin.ignore();
        getline(cin, input);
        cout << "\n\n";
        map <char, int> dictionary;

        for(auto i:input) {
            dictionary[i]++;
        }

        int size =  dictionary.size();
        char arr[size];
        int freq[size];
        int count=0;
        for (auto j: dictionary) {
            arr[count] = j.first;
            freq[count] = j.second;
            count++;
        }
        
        cout << "Character" << "\t\t" << "Frequency" << endl;
        for(int i=0; i<size; i++) {
            cout << arr[i] << "\t\t\t" << freq[i] << endl;
        }
        
        cout << "\n\n";
        cout << "Char | Huffman code ";
        cout << "\n----------------------\n";
        HuffmanCodes(arr, freq, size);
    }

    else if(ans=="IMAGE") {
        int i = 0;
    imageInfo readImage=readBMP();
    unordered_map<int, int> freq;
    unordered_map<int, vector<int>> code;
    unordered_map<int, int>:: iterator itr;
    initCompressedFile();

    sort(readImage.imageMatrix, readImage.imageMatrix+225, comparePixel);
    n = getFrequency(readImage, 225, freq);
    cout<<"Hex \t Frequency \t bit code"<<endl;
    for(itr = freq.begin(); itr != freq.end(); itr++)
    {
        arr[i].setFrequency(itr->first, itr->second);
        i++;
    }

    sort(arr, arr+n, compareFreq);
    huffmancode(arr,n);
    for(int k=0;k<n;k++)
    {
        if(code.find(arr[k].getHex()) == code.end())
            code[arr[k].getHex()] = arr[k].bit;
    }

    for(int k = 0; k<n; k++)
    {
        cout << arr[k].getHex() << "\t" << arr[k].getFreq() << "\t";
        vector<int> :: iterator itr1;
        for(itr1 = arr[k].bit.begin(); itr1 != arr[k].bit.end(); itr1++)
            {
                cout << *itr1;
            }
        cout << endl;
    }
    writeHeader();
    cout<<"Bit Stream"<<endl;
    for(int k=0;k<readImage.sizeim/3;k++)
    {
       vector<int> g = code[readImage.imageMatrix[k].getHex()];
       vector<int> :: iterator itr1;
        for(itr1 = g.begin(); itr1 != g.end(); itr1++)
            {
                writeBitToFile(*itr1,compressedFile);
                cout << *itr1;
            }
    }
    fclose(compressedFile);
    fwrite(&current_byte,1,1,compressedFile);
    }
    else {
        cout << "Wrong input.";
    }
    return 0;
}