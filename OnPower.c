/*
 * Phidget Hello World Program for all devices
 * (c) Phidgets 2012
 */


#include <stdio.h>
#include <phidget21.h>



// -------------------- Event Functions ---------------------------------------

int CCONV AttachHandler (CPhidgetHandle device, void *userptr) {

    int serialNumber;
    const char *name;
    
    LocalErrorCatcher(
        CPhidget_getDeviceName(device, &name));
    LocalErrorCatcher(
        CPhidget_getSerialNumber(device, &serialNumber));
    
//    printf("Hello Device %s, Serial Number: %d\n", name, serialNumber);
    
   
    return 0;
}

int CCONV DetachHandler (CPhidgetHandle device, void *userptr) {

    int serialNumber;
    const char *name;
    
    LocalErrorCatcher(
        CPhidget_getDeviceName(device, &name));
    LocalErrorCatcher(
        CPhidget_getSerialNumber(device, &serialNumber));
    
//    printf("Goodbye Device %s, Serial Number: %d\n", name, serialNumber);
    
    return 0;
}

// When using an error handler with the manager, it takes a
// CPhidgetManagerHandle, when using an individual object, the
// object serves as its own handle.
int CCONV ErrorHandler (CPhidgetHandle device, void *usrptr, 
                    int errorCode, const char *errorDescription) {
    printf("Error Event: %d - %s\n", errorCode, errorDescription);
    return 0;
}

// This error handler can handle any CPhidget function that returns an int
int LocalErrorCatcher (int errorCode) {
	
	const char *errorDescription;
    
	// If the error code is 0, everything is okay
    if (errorCode != 0) {
    
        // Otherwise, you can print specific messages or perform actions by error value.
        switch (errorCode) {
           default:
               printf("Error: An error occurred with code %d.\n", errorCode);
               
               LocalErrorCatcher(
                   CPhidget_getErrorDescription (errorCode, &errorDescription));
               printf("The description for this error is: %s\n", errorDescription);
               break;
       }
    }
	return 0;
}

// -------------------- Main Code ---------------------------------------------

int main(int argc, char* argv[]) {

    int result, numOutputs = 3, state = 0; 
    const char *err, *ptr;
    CPhidgetInterfaceKitHandle phid = 0;

    LocalErrorCatcher(CPhidgetInterfaceKit_create(&phid));
    
    LocalErrorCatcher(CPhidget_set_OnAttach_Handler((CPhidgetHandle) phid, AttachHandler, NULL));
    LocalErrorCatcher(CPhidget_set_OnDetach_Handler((CPhidgetHandle) phid, DetachHandler, NULL));
    LocalErrorCatcher(CPhidget_set_OnError_Handler((CPhidgetHandle) phid, ErrorHandler, NULL));

//    printf("Phidget Simple Playground (plug and unplug devices)\n");
//    printf("Opening...\n");
    LocalErrorCatcher(CPhidget_open((CPhidgetHandle) phid, -1));
    LocalErrorCatcher(CPhidget_waitForAttachment((CPhidgetHandle) phid, 100000));

    CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
    CPhidgetInterfaceKit_getOutputCount(phid, &numOutputs);
//    printf("%s\n", ptr);

    printf("Turning power on\n");			    
    CPhidgetInterfaceKit_setOutputState(phid, 0, 1);
	
	printf("done\n");
    LocalErrorCatcher(CPhidget_close((CPhidgetHandle) phid));
    LocalErrorCatcher(CPhidget_delete((CPhidgetHandle) phid));

    return 0;
}
