#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <time.h>

#define _WIN32_WINNT 0x0500
#include <windows.h>

int acc =0;

using namespace std;

struct node
{
    float value;
    float act_value;
};

struct neuron
{
    float weight;
};

int init ( neuron input_to_hidden_neuron[16][144] , neuron hidden_to_output_neuron[10][16] , int n , int m)
{
	srand(time(0));

    for (int i=0;i<16;i++)
    {
        for (int j=0;j<144;j++)
        {
            input_to_hidden_neuron[i][j].weight = ((float)rand() / (double)RAND_MAX) * 0.2 - 0.1;
        }
    }

    for (int i=0;i<10;i++)
    {
        for (int j=0;j<16;j++)
        {
            hidden_to_output_neuron[i][j].weight =((float)rand() / (double)RAND_MAX) * 0.2 - 0.1;
        }
    }
    return 0;
}

int feedforward (node input_node[][24*24], int no , int actual_output[],int display=0)
{
    vector< vector <node> > input_node_temp (28, vector<node>(28));

    ifstream fin;

    fin.open("train-labels.idx1-ubyte" ,ios::binary);

    unsigned char temp;

    fin.seekg(8+(no-1)*(sizeof(temp)),ios::beg);

    fin.read((char*)&temp,sizeof(temp));

    if ((int)temp/2 >= 1 )
    {
        fin.close();
        return -1;
    }

    for (int k=0;k<10;k++)
    {
        actual_output[k]=0;
    }

    actual_output[(int)temp] = 1;

    fin.close();

    fin.open("train-images.idx3-ubyte",ios::binary);

    fin.seekg(16+(no-1)*28*28,ios::beg);

    for (int i=0;i<28;i++)
    {
        for (int j=0;j<28;j++)
        {
            fin.read((char*)&temp,sizeof(temp));

            input_node_temp[j][i].value = (int)temp > 128 ? 1 : 0;

            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node_temp[j][i].value*255,input_node_temp[j][i].value*255,input_node_temp[j][i].value*255);

                //Draw pixels

                SetPixel(mydc,j,i,COLOR);
            }
        }
    }
    if (display == 1)
        cin>>temp;

    for (int i=2;i<26;i++)
    {
        for (int j=2;j<26;j++)
        {
            if (input_node_temp[i-2][j-2].value == 1 && input_node_temp[i+2][j+2].value == 1 && input_node_temp[i-1][j-1].value == 1 && input_node_temp[i][j].value==1 && input_node_temp[i+1][j+1].value ==1 && input_node_temp[i][j].value==1)
            {
                input_node[0][(i-2)*24+(j-2)].value = 1;
            }
            else
            {
                input_node[0][(i-2)*24+(j-2)].value = 0;
            }
            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node[0][(i-2)*24+(j-2)].value*255,input_node[0][(i-2)*24+(j-2)].value*255,input_node[0][(i-2)*24+(j-2)].value*255);

                //Draw pixels

                SetPixel(mydc,i+30,j,COLOR);
            }
        }
    }
    for (int i=2;i<26;i++)
    {
        for (int j=2;j<26;j++)
        {
            if (input_node_temp[i-2][j].value == 1 && input_node_temp[i+2][j].value == 1 && input_node_temp[i-1][j].value == 1 && input_node_temp[i][j].value==1 && input_node_temp[i+1][j].value ==1)
            {
                input_node[1][(i-2)*24+(j-2)].value = 1;
            }
            else
            {
                input_node[1][(i-2)*24+(j-2)].value = 0;
            }
            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node[1][(i-2)*24+(j-2)].value*255,input_node[1][(i-2)*24+(j-2)].value*255,input_node[1][(i-2)*24+(j-2)].value*255);

                //Draw pixels

                SetPixel(mydc,i+60,j,COLOR);
            }
        }
    }
     for (int i=2;i<26;i++)
    {
        for (int j=2;j<26;j++)
        {
            if (input_node_temp[i+2][j-2].value == 1 && input_node_temp[i+1][j-1].value == 1 && input_node_temp[i-1][j+1].value == 1 && input_node_temp[i][j].value==1 && input_node_temp[i-2][j+2].value ==1)
            {
                input_node[2][(i-2)*24+(j-2)].value = 1;
            }
            else
            {
                input_node[2][(i-2)*24+(j-2)].value = 0;
            }
            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node[2][(i-2)*24+(j-2)].value*255,input_node[2][(i-2)*24+(j-2)].value*255,input_node[2][(i-2)*24+(j-2)].value*255);

                //Draw pixels

                SetPixel(mydc,i+90,j,COLOR);
            }
        }
    }


     for (int i=2;i<26;i++)
    {
        for (int j=2;j<26;j++)
        {
             if (input_node_temp[i][j-2].value == 1 && input_node_temp[i][j-1].value == 1 && input_node_temp[i][j+1].value == 1 && input_node_temp[i][j].value==1 && input_node_temp[i][j+2].value ==1)
            {
                input_node[3][(i-2)*24+(j-2)].value = 1;
            }
            else
            {
                input_node[3][(i-2)*24+(j-2)].value = 0;
            }
            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node[3][(i-2)*24+(j-2)].value*255,input_node[3][(i-2)*24+(j-2)].value*255,input_node[3][(i-2)*24+(j-2)].value*255);

                //Draw pixels

                SetPixel(mydc,i+120,j,COLOR);
            }
        }
    }

    fin.close();

  return 0;

}

int feedforward_test (node input_node[][24*24], int no , int actual_output[],int display=0)
{
    vector< vector <node> > input_node_temp (28, vector<node>(28));

    ifstream fin;

    unsigned char temp;

    fin.open("t10k-labels.idx1-ubyte" ,ios::binary);

    fin.seekg(8+(no-1)*(sizeof(temp)),ios::beg);

    fin.read((char*)&temp,sizeof(temp));

    if ((int)temp/2 >= 1 )
    {
        fin.close();
        return -1;
    }

    for (int k=0;k<10;k++)
    {
        actual_output[k]=0;
    }

    actual_output[(int)temp] = 1;

    fin.close();

    fin.open("t10k-images.idx3-ubyte",ios::binary);

    fin.seekg(16+(no-1)*28*28,ios::beg);

    for (int i=0;i<28;i++)
    {
        for (int j=0;j<28;j++)
        {
            fin.read((char*)&temp,sizeof(temp));

            input_node_temp[j][i].value = (int)temp > 128 ? 1 : 0;

            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node_temp[j][i].value*255,input_node_temp[j][i].value*255,input_node_temp[j][i].value*255);

                //Draw pixels

                SetPixel(mydc,j,i,COLOR);
            }
        }
    }
    if (display == 1)
        cin>>temp;

    for (int i=2;i<26;i++)
    {
        for (int j=2;j<26;j++)
        {
            if (input_node_temp[i-2][j-2].value == 1 && input_node_temp[i+2][j+2].value == 1 && input_node_temp[i-1][j-1].value == 1 && input_node_temp[i][j].value==1 && input_node_temp[i+1][j+1].value ==1 && input_node_temp[i][j].value==1)
            {
                input_node[0][(i-2)*24+(j-2)].value = 1;
            }
            else
            {
                input_node[0][(i-2)*24+(j-2)].value = 0;
            }
            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node[0][(i-2)*24+(j-2)].value*255,input_node[0][(i-2)*24+(j-2)].value*255,input_node[0][(i-2)*24+(j-2)].value*255);

                //Draw pixels

                SetPixel(mydc,i+30,j,COLOR);
            }
        }
    }
    for (int i=2;i<26;i++)
    {
        for (int j=2;j<26;j++)
        {
            if (input_node_temp[i-2][j].value == 1 && input_node_temp[i+2][j].value == 1 && input_node_temp[i-1][j].value == 1 && input_node_temp[i][j].value==1 && input_node_temp[i+1][j].value ==1)
            {
                input_node[1][(i-2)*24+(j-2)].value = 1;
            }
            else
            {
                input_node[1][(i-2)*24+(j-2)].value = 0;
            }
            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node[1][(i-2)*24+(j-2)].value*255,input_node[1][(i-2)*24+(j-2)].value*255,input_node[1][(i-2)*24+(j-2)].value*255);

                //Draw pixels

                SetPixel(mydc,i+60,j,COLOR);
            }
        }
    }
     for (int i=2;i<26;i++)
    {
        for (int j=2;j<26;j++)
        {
            if (input_node_temp[i+2][j-2].value == 1 && input_node_temp[i+1][j-1].value == 1 && input_node_temp[i-1][j+1].value == 1 && input_node_temp[i][j].value==1 && input_node_temp[i-2][j+2].value ==1)
            {
                input_node[2][(i-2)*24+(j-2)].value = 1;
            }
            else
            {
                input_node[2][(i-2)*24+(j-2)].value = 0;
            }
            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node[2][(i-2)*24+(j-2)].value*255,input_node[2][(i-2)*24+(j-2)].value*255,input_node[2][(i-2)*24+(j-2)].value*255);

                //Draw pixels

                SetPixel(mydc,i+90,j,COLOR);
            }
        }
    }


     for (int i=2;i<26;i++)
    {
        for (int j=2;j<26;j++)
        {
             if (input_node_temp[i][j-2].value == 1 && input_node_temp[i][j-1].value == 1 && input_node_temp[i][j+1].value == 1 && input_node_temp[i][j].value==1 && input_node_temp[i][j+2].value ==1)
            {
                input_node[3][(i-2)*24+(j-2)].value = 1;
            }
            else
            {
                input_node[3][(i-2)*24+(j-2)].value = 0;
            }
            if (display==1)
            {

                HWND myconsole = GetConsoleWindow();

                //Get a handle to device context

                HDC mydc = GetDC(myconsole);

                //Choose any color

                COLORREF COLOR;

                COLOR= RGB(input_node[3][(i-2)*24+(j-2)].value*255,input_node[3][(i-2)*24+(j-2)].value*255,input_node[3][(i-2)*24+(j-2)].value*255);

                //Draw pixels

                SetPixel(mydc,i+120,j,COLOR);
            }
        }
    }

    fin.close();

  return 0;

}


void input_to_hidden_weighted_sum( node input_node[][24*24], neuron input_to_hidden_neuron [][12*12] ,node hidden_node[4][4], int n, int m)
{
    for (int i=0;i<n-4;i++)
    {
        for (int j=0;j<m-4;j++)
        {
            hidden_node[0][((i%24)/12)+(j/(24*12))].value = 0;
            hidden_node[1][((i%24)/12)+(j/(24*12))].value = 0;
            hidden_node[2][((i%24)/12)+(j/(24*12))].value = 0;
            hidden_node[3][((i%24)/12)+(j/(24*12))].value = 0;
        }
    }
	for (int i=0;i<n-4;i++)
    {
        for (int j=0;j<m-4;j++)
        {
            for (int k=0;k<144;k++)
            {
                hidden_node[0][((i%24)/12)+(j/(24*12))].value += input_node[0][i*24+j].value * input_to_hidden_neuron[0+((i%24)/12)+(j/(24*12))][k].weight;
                hidden_node[1][((i%24)/12)+(j/(24*12))].value += input_node[1][i*24+j].value * input_to_hidden_neuron[4+((i%24)/12)+(j/(24*12))][k].weight;
                hidden_node[2][((i%24)/12)+(j/(24*12))].value += input_node[2][i*24+j].value * input_to_hidden_neuron[8+((i%24)/12)+(j/(24*12))][k].weight;
                hidden_node[3][((i%24)/12)+(j/(24*12))].value += input_node[3][i*24+j].value * input_to_hidden_neuron[12+((i%24)/12)+(j/(24*12))][k].weight;
            }
        }
    }
}

void activation_hidden (node hidden_node [4][4], int n, int m)
{
	for (int i=0; i<(n-4)*(m-4) ;i++)
	{
		hidden_node[0][i].act_value = tanh (hidden_node[0][i].value);
		hidden_node[1][i].act_value = tanh (hidden_node[1][i].value);
		hidden_node[2][i].act_value = tanh (hidden_node[2][i].value);
		hidden_node[3][i].act_value = tanh (hidden_node[3][i].value);
	}
}

void hidden_to_output_weighted_sum (node output_node[] , neuron hidden_to_output_neuron [][16],  node hidden_node[4][4] , int n, int m)
{
	for (int j=0;j<10;j++)
	{
		output_node[j].value = 0;

		for (int i=0; i<16 ;i++)
		{
			output_node[j].value += hidden_node[i/4][i%4].act_value * hidden_to_output_neuron[j][i].weight;
		}
	}
}

int softmax (node output_node[] ,float output_error[], float prob[] , float sum,float &mloss,int actual_output[])
{
	sum=0;

	for (int i=0;i<10;i++)
	{
		prob[i] = exp (output_node[i].value);
		sum += prob[i];
	}

	for (int i=0;i<10;i++)
	{
		prob[i] = prob[i]/sum;
		output_error[i] = prob[i]- actual_output[i];

		//cout<<"Outptut - "<<prob[i]<<"\t Actual output - "<<actual_output[i]<<endl;
	}
	float loss=0;

	for (int i=0;i<10;i++)
	{
		loss -= actual_output[i] * log(prob[i]);
	}

    mloss +=loss;

	return 0;
}

int softmax_test (node output_node[] ,float output_error[], float prob[] , float sum,int actual_output[])
{
	sum=0;int flag=0,maxpro,act;
	float rms_error[10];

	for (int i=0;i<10;i++)
	{
		prob[i] = exp (output_node[i].value);
		sum += prob[i];
	}
	maxpro=0;act=0;
	for (int i=0;i<10;i++)
	{
		prob[i] = prob[i]/sum;
		output_error[i] = prob[i]- actual_output[i];

		if (prob[maxpro]<prob[i])
            maxpro = i;

        if (actual_output[i]==1)
            act=i;
		//cout<<"Outptut - "<<prob[i]<<"\t Actual output - "<<actual_output[i]<<endl;

		rms_error[i] = (actual_output[i] - prob[i])*(actual_output[i] - prob[i]);

		if (prob[i] != prob[i])
		{
			flag =1;
		}

	}

	rms_error[0] /= 10;
	rms_error[0] = sqrt(rms_error[0]);

	float loss=0;
	for (int i=0;i<10;i++)
	{
		loss -= actual_output[i] * log(prob[i]);
	}
	//cout<<"\nloss - "<<loss<<endl;

	fstream fout;

	fout.open ("error_test.csv", ios::out|ios::app);

	//cout<<"\nRms ERROR - "<<rms_error[0]<<endl;

	fout<<"\n"<<loss<<" , "<<rms_error[0]<<" , ";

	if (actual_output[maxpro] == 1)
	{
	    //cout<<actual_output[maxpro]<<endl;
        fout<<"1 , "<<act;
        acc++;
	}
	else
        fout<<"0 , "<<act;

	fout.close();

	if ((rms_error[0] == 0 && (loss == 0 || loss != loss ))  || flag== 1)
	{
		//return 1;
	}
	return 0;
}


void backpropogation (node input_node[4][24*24],node hidden_node[4][4],node output_node[], neuron input_to_hidden_neuron[16][12*12], neuron hidden_to_output_neuron[10][16],float output_error[] , int n , int m)
{

    neuron delta_weight_output [10][16];

	neuron delta_weight_input [16][144];


		for (int i=0;i<10 ;i++)
		{
			for (int j=0;j<16;j++)
			{
				delta_weight_output[i][j].weight = hidden_node[j/4][j%4].act_value * output_error[i];
			}
		}
		for (int i=0;i<16;i++)

			hidden_node[i/4][i%4].act_value=0;

        for (int j=0;j<16;j++)
        {
            for (int i=0;i<10;i++)
            {
                hidden_node[j/4][j%4].act_value += hidden_to_output_neuron[i][j].weight * output_error[i];
            }
 		}

 		for (int i=0;i<16;i++)

            hidden_node[i/4][i%4].value =  hidden_node[i/4][i%4].act_value	* (1 - pow (tanh (hidden_node[i/4][i%4].value), 2));


	for (int i=0;i<n-4;i++)
    {
        for (int j=0;j<m-4;j++)
        {
            for (int k=0;k<144;k++)
            {
                delta_weight_input[0+((i%24)/12)+(j/(24*12))][k].weight = hidden_node[0][((i%24)/12)+(j/(24*12))].value * input_node[0][i*24+j].value;
                delta_weight_input[4+((i%24)/12)+(j/(24*12))][k].weight = hidden_node[1][((i%24)/12)+(j/(24*12))].value * input_node[1][i*24+j].value;
                delta_weight_input[8+((i%24)/12)+(j/(24*12))][k].weight = hidden_node[2][((i%24)/12)+(j/(24*12))].value * input_node[2][i*24+j].value;
                delta_weight_input[12+((i%24)/12)+(j/(24*12))][k].weight = hidden_node[3][((i%24)/12)+(j/(24*12))].value * input_node[3][i*24+j].value;
            }
        }
    }


    for (int i=0;i<16;i++)
    {
        for (int j=0;j<144;j++)
        {
            input_to_hidden_neuron[i][j].weight -= delta_weight_input[i][j].weight * 0.05;
        }
    }

    for (int j=0;j<10;j++)
	{
		for (int i=0;i<16 ;i++)
		{
            hidden_to_output_neuron[j][i].weight -= delta_weight_output[j][i].weight * 0.05;
        }
    }

}

void restore_weight (neuron input_to_hidden_neuron[16][144] ,neuron hidden_to_output_neuron[10][16] ,int n,int m)
{
		fstream fin;
	fin.open("weight.txt",ios::in);

    int count=0;

	for (int i=0;i<16;i++)
    {
        for (int j=0;j<144;j++)
        {
            char temp[20];
            float fol;
            count++;
           fin>>temp;
           char* pEnd;
           fol = strtof (temp,&pEnd);
           //cout<<fol<<endl;
            input_to_hidden_neuron[i][j].weight=fol/100;
        }
    }
    for (int i=0;i<10;i++)
    {
        for (int j=0;j<16;j++)
        {
            char temp[20];
            float fol;
            count++;
           fin>>temp;
           char* pEnd;
           fol = strtof (temp,&pEnd);
           //cout<<fol<<endl;
		   hidden_to_output_neuron[i][j].weight=fol/100;
        }
    }
    fin.close();
}

void store_weight (neuron input_to_hidden_neuron[16][144] ,neuron hidden_to_output_neuron[10][16] ,int n,int m)
{
	fstream fout;

	fout.open("weight.txt",ios::out);

	for (int i=0;i<16;i++)
    {
        for (int j=0;j<144;j++)
        {
        	float temp;
        	temp=input_to_hidden_neuron[i][j].weight * 100;
          	fout<<temp<<" ";
        }
    }

    for (int i=0;i<10;i++)
    {
        for (int j=0;j<16;j++)
        {
        	float temp;
        	temp = hidden_to_output_neuron[i][j].weight*100;
           fout<<temp<<" ";
        }
    }
    fout.close();
}

int main(int argc, char** argv)
{

	fstream fout;
	fout.open ("error_train.csv", ios::out|ios::trunc);
	fout<<"Loss";
	fout.close();

	fout.open ("error_test.csv", ios::out|ios::trunc);
	fout<<"Loss,RMS Error,Right,Digit";
	fout.close();


	fstream fin;

    fin.open ("config.txt",ios::in);

    int h, w;

    fin>>h;
    fin>>w;

    fin.close();

	float output_error[10];

    node input_node [4][24*24];

    node hidden_node [4][4];

    node output_node [10];

    neuron input_to_hidden_neuron [16][144];

    neuron hidden_to_output_neuron [10][16];

	int tra,temp_tra;
    int total_iter,iter;
    int actual_output[10];
    float prob[12];
    float sum=0,mloss=0;

	int ch1,ch2,ch3;

if( 1 == 1)
	{
		tra =20;
		temp_tra=tra;
		total_iter=10000;
		ch1=0;
		ch2=1;
		ch3=0;
	}

	//cout<<"Restore weights? - ";
	//cin>>ch1;


    cout<<"\n\n\t Training - \n\n\t";
    for (float i=0;i<=25;i++)
        cout<<char(178);
    cout<<"\r\t";

   	if (ch1==1)
    {
    	restore_weight (input_to_hidden_neuron,  hidden_to_output_neuron , h , w);
	}
	else
	{
		init ( input_to_hidden_neuron,  hidden_to_output_neuron , h , w);
	}

    int c=0;
	do
	{
    iter=0;

    mloss=0;

	while (iter++ <total_iter )
    {

    	//cout<<"Training No - "<<c++<<endl;
    	c++;

        if(feedforward(input_node,iter,actual_output,0) == -1)
            continue;

   	    input_to_hidden_weighted_sum(input_node , input_to_hidden_neuron, hidden_node , h, w);

    	activation_hidden (hidden_node, h, w);

    	hidden_to_output_weighted_sum (output_node , hidden_to_output_neuron,  hidden_node ,h,w);

    	softmax (output_node,output_error,prob,sum,mloss,actual_output);

        backpropogation (input_node,hidden_node,output_node,input_to_hidden_neuron,hidden_to_output_neuron,output_error , h, w);

        char fin=176, rem=178;

        for (float i=0;i<float(c*25/(tra*(total_iter+0.0)));i++)
            cout<<fin;

        for (float i=float(c*25/(tra*(total_iter+0.0)));i<=25;i++)
          cout<<rem;

        cout<<"\r"<<"\t";

    }
        fstream fout1;
        fout1.open ("error_train.csv", ios::out|ios::app|ios::binary);
        fout1<<"\n"<<mloss/total_iter;
        fout1.close();

	}while (--temp_tra>0);

	for (float i=0;i<=25;i++)
        cout<<char(176);

    if(ch2==1)
    {
        store_weight (input_to_hidden_neuron,hidden_to_output_neuron,h,w);
    }

    cout<<"\n\n\t Testing - \n\n\t";
    for (float i=0;i<=25;i++)
        cout<<char(178);
    cout<<"\r\t";

	//cout<<"Test? - ";
	//cin>>ch3;
	 if (ch3!=-1)
     {
         iter=1;
         total_iter=10000;

	while (iter++ <total_iter )
    {

    	//cout<<"Training No -"<<(total_iter)<<endl;

       if(feedforward_test(input_node,iter,actual_output,0) == -1)
            continue;

   	   input_to_hidden_weighted_sum(input_node , input_to_hidden_neuron, hidden_node , h, w);

    	activation_hidden (hidden_node, h, w);

    	hidden_to_output_weighted_sum (output_node , hidden_to_output_neuron,  hidden_node ,h,w);

    	softmax_test (output_node,output_error,prob,sum,actual_output);

    	backpropogation (input_node,hidden_node,output_node,input_to_hidden_neuron,hidden_to_output_neuron,output_error , h, w);

    	 char fin=176, rem=178;

	 for (float i=0;i<iter*25/(total_iter*1.0);i++)
        cout<<fin;

     for (float i=iter*25/(total_iter*1.0);i<=25;i++)
        cout<<rem;

    cout<<"\r\t";
	}
    }

     for (float i=0;i<=25;i++)
        cout<<char(176);

     cout<<"\n\n\t Accuracy = "<<acc;

	return 0;

}
