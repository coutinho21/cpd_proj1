#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>

using namespace std;

#define SYSTEMTIME clock_t

void OnMult(int m_ar, int m_br)
{

	SYSTEMTIME Time1, Time2;

	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;

	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for (i = 0; i < m_ar; i++)
		for (j = 0; j < m_ar; j++)
			pha[i * m_ar + j] = (double)1.0;

	for (i = 0; i < m_br; i++)
		for (j = 0; j < m_br; j++)
			phb[i * m_br + j] = (double)(i + 1);

	Time1 = clock();

	for (i = 0; i < m_ar; i++)
	{
		for (j = 0; j < m_br; j++)
		{
			temp = 0;
			for (k = 0; k < m_ar; k++)
			{
				temp += pha[i * m_ar + k] * phb[k * m_br + j];
			}
			phc[i * m_ar + j] = temp;
		}
	}

	Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	// display 10 elements of the result matrix to verify correctness
	cout << "Result matrix: " << endl;
	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < min(10, m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;

	free(pha);
	free(phb);
	free(phc);
}

// add code here for line x line matriz multiplication
void OnMultLine(int m_ar, int m_br)
{

	SYSTEMTIME Time1, Time2;
	char st[100];
	double *pha, *phb, *phc;
	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	// Initialize matrices
	for (int i = 0; i < m_ar; i++)
		for (int j = 0; j < m_ar; j++)
			pha[i * m_ar + j] = (double)1.0;

	for (int i = 0; i < m_br; i++)
		for (int j = 0; j < m_br; j++)
			phb[i * m_br + j] = (double)(i + 1);

	Time1 = clock();

	int option;
	cout << "Option :";
	cin >> option;

	if (option == 1)
	{

	#pragma omp parallel for
		for (int i = 0; i < m_ar; i++)
			for (int k = 0; k < m_ar; k++)
				for (int j = 0; j < m_br; j++)
				{
					phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_br + j];
				}
	}
	else if (option == 2)
	{
		#pragma omp parallel
		for (int i = 0; i < m_ar; i++)
			for (int k = 0; k < m_ar; k++)
		#pragma omp for
				for (int j = 0; j < m_br; j++)
				{
					phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_br + j];
				}
	}
	else {
		  for(int i=0; i<m_ar; i++)	
    {    for(int  k=0; k<m_ar; k++ )
        { for(int j=0; j<m_br; j++)
            {    
                phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_br+j];
            }
        }
    }
	}

	Time2 = clock();
	sprintf(st, "Time: %3.5f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < min(10, m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;

	free(pha);
	free(phb);
	free(phc);
}

// add code here for block x block matriz multiplication
void OnMultBlock(int m_ar, int m_br, int bkSize)
{
	SYSTEMTIME Time1, Time2;
	char st[100];
	double *pha, *phb, *phc;
	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	// Initialize matrices
	for (int i = 0; i < m_ar; i++)
		for (int j = 0; j < m_ar; j++)
			pha[i * m_ar + j] = (double)1.0;

	for (int i = 0; i < m_br; i++)
		for (int j = 0; j < m_br; j++)
			phb[i * m_br + j] = (double)(i + 1);

	Time1 = clock();

	// Perform block matrix multiplication
	for (int ii = 0; ii < m_ar; ii += bkSize)
	{
		for (int jj = 0; jj < m_br; jj += bkSize)
		{
			for (int kk = 0; kk < m_ar; kk += bkSize)
			{
				// Multiply each block
				for (int i = ii; i < min(ii + bkSize, m_ar); i++)
				{
					for (int j = jj; j < min(jj + bkSize, m_br); j++)
					{
						double temp = 0;
						for (int k = kk; k < min(kk + bkSize, m_ar); k++)
						{
							temp += pha[i * m_ar + k] * phb[k * m_br + j];
						}
						phc[i * m_ar + j] = temp;
					}
				}
			}
		}
	}

	Time2 = clock();
	sprintf(st, "Time: %3.5f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	// Display 10 elements of the result matrix to verify correctness
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < min(10, m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;

	free(pha);
	free(phb);
	free(phc);
}

void handle_error(int retval)
{
	printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
	exit(1);
}

void init_papi()
{
	int retval = PAPI_library_init(PAPI_VER_CURRENT);
	if (retval != PAPI_VER_CURRENT && retval < 0)
	{
		printf("PAPI library version mismatch!\n");
		exit(1);
	}
	if (retval < 0)
		handle_error(retval);

	std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
			  << " MINOR: " << PAPI_VERSION_MINOR(retval)
			  << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}

int main(int argc, char *argv[])
{

	char c;
	int lin, col, blockSize;
	int op;

	int EventSet = PAPI_NULL;
	long long values[3];
	int ret;

	ret = PAPI_library_init(PAPI_VER_CURRENT);
	if (ret != PAPI_VER_CURRENT)
		std::cout << "FAIL" << endl;

	ret = PAPI_create_eventset(&EventSet);
	if (ret != PAPI_OK)
		cout << "ERROR: create eventset" << endl;

	ret = PAPI_add_event(EventSet, PAPI_L1_DCM);
	if (ret != PAPI_OK)
		cout << "ERROR: PAPI_L1_DCM" << endl;

	ret = PAPI_add_event(EventSet, PAPI_L2_DCM);
	if (ret != PAPI_OK)
		cout << "ERROR: PAPI_L2_DCM" << endl;

	ret = PAPI_add_event(EventSet, PAPI_FP_OPS);
	if (ret != PAPI_OK)
		cout << "ERROR: PAPI_FP_OPS" << endl;

	op = 1;
	do
	{
		cout << endl
			 << "1. Multiplication" << endl;
		cout << "2. Line Multiplication" << endl;
		cout << "3. Block Multiplication" << endl;
		cout << "Selection?: ";
		cin >> op;
		if (op == 0)
			break;
		printf("Dimensions: lins=cols ? ");
		cin >> lin;
		col = lin;

		// Start counting
		ret = PAPI_start(EventSet);
		if (ret != PAPI_OK)
			cout << "ERROR: Start PAPI" << endl;

		switch (op)
		{
		case 1:
			OnMult(lin, col);
			break;
		case 2:
			OnMultLine(lin, col);
			break;
		case 3:
			cout << "Block Size? ";
			cin >> blockSize;
			OnMultBlock(lin, col, blockSize);
			break;
		}

		ret = PAPI_stop(EventSet, values);
		if (ret != PAPI_OK)
			cout << "ERROR: Stop PAPI" << endl;
		printf("L1 DCM: %lld \n", values[0]);
		printf("L2 DCM: %lld \n", values[1]);
		printf("FP_OPS: %lld \n", values[2]);

		ret = PAPI_reset(EventSet);
		if (ret != PAPI_OK)
			std::cout << "FAIL reset" << endl;

	} while (op != 0);

	ret = PAPI_remove_event(EventSet, PAPI_L1_DCM);
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event" << endl;

	ret = PAPI_remove_event(EventSet, PAPI_L2_DCM);
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event" << endl;

	ret = PAPI_remove_event(EventSet, PAPI_FP_OPS);
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event" << endl;

	ret = PAPI_destroy_eventset(&EventSet);
	if (ret != PAPI_OK)
		std::cout << "FAIL destroy" << endl;
}
