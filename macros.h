/* Macros for function addEvent() */

#define emptyDelFail "Unable to delete empty file of user!\n"
#define fopenError "ERROR! Unable to open the user's file!\n"
#define wrongUsageAdd "Number of arguments is wrong! Usage is <username> add <date> <time1> <time2> <name>\n"
#define dateErrorPast "ERROR! The time and the date should be in the future and of valid format.\n"
#define dateErrorDuration "ERROR! End time of the event must be same or after the start time.\n"
#define clashError "Your current input event clashes with another event in your Calendar.\n"
#define addSuccess "The event was successfully added to your Calendar.\n"

#define noExistError "ERROR! User's file doesn't exist."
#define wrongUsageRemove "Number of arguments is wrong. Usage is <username> remove <date> <time1>\n"
#define removeSuccess "The event has successfully been removed.\n"
#define removeFail "The event could not be removed! Please check your query and try again.\n"

#define wrongUsageUpdate "Number of arguments is wrong. Usage is <username> update <date> <time1> <time2> <name>\n"
#define updateSuccess "The event has successfuly been updated.\n"
#define updateFailAdd "Unable to update the even!\n"
#define updateFailNoExists "Entry does not exist, so cannot be updated.\n"
#define restoredEvent "Unable to add the event because of the above reason.\nThus, update failed and now restoring the original event back.\n"
#define restoredEventFail "Unable to add the event because of the above reason.\n Unable to restore event due to some unknown reason.\n"
#define exactMatchingUpdate "This exact event already exists, so no update has been done.\n"

#define queryInvalid "Failed to modify your Calendar: Invalid operation specified.\nOnly 'add', 'remove', 'update', 'get' and 'getall' are supported\n"
#define queryPass "Your query was successfully completed.\n"
#define queryFail "Your operation could not be completed because of the error described above ^.\n Please check and try again.\n"

#define wrongUsageGet "ERROR: Invalid query. Usage is either of the two forms:\n1. <username> get <eventDate>\n2. <username> get <eventDate> <eventStartTime>\n"
#define getSuccess "The event(s) is(are) as shown above.\n"
#define getFail "Your request to get the events has failed.\n"
#define getNoEntry "There is no entry corresponding to this date and time.\n"

#define totalLines " number of events are present for this user.\n"
#define getLineSuccess "Event Number "
#define getLineWrongLine "The client sent a request for getting an event that doesn't exist.\n"
#define wrongUsageGetLine "The client sent a wrong format of request to get the nth line.\n"
#define wrongUsageGetAll "Wrong usage of getall. Usage is username getall.\n"
#define restoreSuccess "Restored original event.\n"

#define FOLDER_NAME "./Calendar/"
