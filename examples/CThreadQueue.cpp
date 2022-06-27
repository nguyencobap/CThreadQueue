#include "BACThread.h"
#include <stdio.h>


int main(int argc, char const *argv[])
{
	BACThread* pHandlerThread = new BACThread("My Thread");
    int result = pHandlerThread->Start();
    if (result != 0)
    {
        printf("pHandlerThread->Start() failed ret = %d \n", result);
    } else {
    	printf("pHandlerThread->Start() success = %d \n", result);
    }


  	//Function pointer with input is a void pointer object that use want to use inside thread.
  	FuncPtr loopFuntion1 = [](void* arg) {
  		int n = *((int*)arg);
  		int i = 0;
  	    while (i < n) {
  	    	i++;
  	    	printf("loop inside thread i = %d \n",i);
  	    }
  	};

  	FuncPtr loopFuntion2 = [](void* arg) {
  		int n = *((int*)arg);
  		int i = 0;
  	    while (i < n) {
  	    	i++;
  	    	printf("loop inside thread i2 = %d \n",i);
  	    }
  	};

  	int numLoop = 1000;

    //Post the loop function pointer 1that created earlier and num loop to use inside thread.
    pHandlerThread->Post(loopFuntion1, &numLoop);
    //Post the loop function pointer 2 that created earlier and num loop to use inside thread, this loop will execute after loop function 1 done.
    pHandlerThread->Post(loopFuntion2, &numLoop);

    //Loop outside thread for testing, this loop will not be block by 2 above loop.
    int o = 0;
    while(o < numLoop) {
    	o++;
    	printf("loop outside thread o = %d \n",o);
    }

    //This keep main running until all job in thread done, otherwise thread killed when main end, in real life you don't need this.
    while(pHandlerThread->GetNumJobRemaining() > 0) {

    }
}