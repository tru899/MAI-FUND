#include <errno.h>

#ifndef MACROS_H
#define MACROS_H

#ifdef __APPLE__
    #define ERROR_MESSAGES { \
        "Undefined error: 0", \
        "Operation not permitted", \
        "No such file or directory", \
        "No such process", \
        "Interrupted system call", \
        "Input/output error", \
        "No such device or address", \
        "Argument list too long", \
        "Exec format error", \
        "Bad file descriptor", \
        "No child processes", \
        "Resource temporarily unavailable", \
        "Not enough space", \
        "Permission denied", \
        "Bad address", \
        "Block device required", \
        "Device busy", \
        "File exists", \
        "Cross-device link", \
        "No such device", \
        "Not a directory", \
        "Is a directory", \
        "Invalid argument", \
        "Too many open files in system", \
        "Too many open files", \
        "Inappropriate ioctl for device", \
        "Text file busy", \
        "File too large", \
        "No space left on device", \
        "Illegal seek", \
        "Read-only file system", \
        "Too many links", \
        "Broken pipe", \
        "Numerical argument out of domain", \
        "Numerical result out of range", \
        "Resource deadlock avoided", \
        "File name too long", \
        "No locks available", \
        "Function not implemented", \
        "Directory not empty", \
        "Too many symbolic links encountered", \
        "Operation would block", \
        "Value too large for defined data type", \
        "Resource not available", \
        "No message of desired type", \
        "Identifier removed", \
        "Channel number out of range", \
        "Unknown error 44", \
        "Unknown error 45", \
        "Unknown error 46", \
        "Unknown error 47", \
        "Unknown error 48", \
        "Unknown error 49", \
        "Unknown error 50", \
        "Not a socket", \
        "Destination address required", \
        "Message too long", \
        "Protocol wrong type for socket", \
        "Protocol not available", \
        "Protocol not supported", \
        "Socket type not supported", \
        "Operation not supported", \
        "Protocol family not supported", \
        "Address family not supported by protocol", \
        "Address already in use", \
        "Cannot assign requested address", \
        "Network is down", \
        "Network is unreachable", \
        "Network dropped connection on reset", \
        "Software caused connection abort", \
        "Connection reset by peer", \
        "No buffer space available", \
        "Socket is already connected", \
        "Socket is not connected", \
        "Cannot send after transport endpoint shutdown", \
        "Too many references: cannot splice", \
        "Connection timed out", \
        "Connection refused", \
        "Host is down", \
        "No route to host", \
        "Operation already in progress", \
        "Operation now in progress", \
        "Stale NFS file handle", \
        "Structure needs cleaning", \
        "Not a XENIX named type file", \
        "No XENIX semaphores available", \
        "Is a named type file", \
        "Remote I/O error", \
        "Quota exceeded", \
        "No medium found", \
        "Wrong medium type", \
        "Operation Canceled", \
        "Identifier removed", \
        "Stream timeout", \
        "Not a stream", \
        "Protocol error", \
        "Multihop attempted", \
        "Link has been severed", \
        "Advertise error", \
        "Srmount error", \
        "Communication error on send", \
        "No such device", \
        "Quorum not present", \
        "Stale NFS file handle", \
        "File locking deadlock", \
        "Too many users", \
        "Socket operation on non-socket", \
        "Destination address required", \
        "Message too long", \
        "Protocol wrong type for socket", \
        "Protocol not available", \
        "Protocol not supported", \
        "Socket type not supported", \
        "Operation not supported", \
        "Protocol family not supported", \
        "Address family not supported by protocol", \
        "Address already in use", \
        "Cannot assign requested address", \
        "Network is down", \
        "Network is unreachable", \
        "Network dropped connection on reset", \
        "Software caused connection abort", \
        "Connection reset by peer", \
        "No buffer space available", \
        "Socket is already connected", \
        "Socket is not connected", \
        "Cannot send after transport endpoint shutdown", \
        "Too many references: cannot splice", \
        "Connection timed out", \
        "Connection refused", \
        "Host is down", \
        "No route to host", \
        "Transport endpoint is not connected", \
        "Memory page has hardware error" \
    }

#elif __linux__
    #define ERROR_MESSAGES { \
        "Success", \
        "Operation not permitted", \
        "No such file or directory", \
        "No such process", \
        "Interrupted system call", \
        "Input/output error", \
        "No such device or address", \
        "Argument list too long", \
        "Exec format error", \
        "Bad file descriptor", \
        "No child processes", \
        "Resource temporarily unavailable", \
        "Out of memory", \
        "Permission denied", \
        "Bad address", \
        "Block device required", \
        "Device or resource busy", \
        "File exists", \
        "Cross-device link", \
        "No such device", \
        "Not a directory", \
        "Is a directory", \
        "Invalid argument", \
        "Too many open files in system", \
        "Too many open files", \
        "Inappropriate ioctl for device", \
        "Text file busy", \
        "File too large", \
        "No space left on device", \
        "Illegal seek", \
        "Read-only file system", \
        "Too many links", \
        "Broken pipe", \
        "Numerical argument out of domain", \
        "Numerical result out of range", \
        "Resource deadlock avoided", \
        "File name too long", \
        "No locks available", \
        "Function not implemented", \
        "Directory not empty", \
        "Too many symbolic links encountered", \
        "Operation would block", \
        "Value too large for defined data type", \
        "Resource not available", \
        "No message of desired type", \
        "Identifier removed", \
        "Channel number out of range", \
        "Level 2 not synchronized", \
        "Level 3 halted", \
        "Level 3 reset", \
        "Link number out of range", \
        "Protocol driver not attached", \
        "No CSI structure available", \
        "Level 2 halted", \
        "Invalid exchange", \
        "Invalid request descriptor", \
        "Exchange full", \
        "No anode", \
        "Invalid request code", \
        "Invalid slot", \
        "Unknown error 58", \
        "Bad font file format", \
        "Device not a stream", \
        "Bad stream number", \
        "Type not found", \
        "Protocol not available", \
        "Not a data message", \
        "No message available", \
        "Value too large", \
        "Operation canceled", \
        "Identifier removed", \
        "Channel number out of range", \
        "Unknown error 71", \
        "Unknown error 72", \
        "Unknown error 73", \
        "Unknown error 74", \
        "Bad executable (or shared library) format", \
        "Bad address", \
        "Not a socket", \
        "Destination address required", \
        "Message too long", \
        "Protocol wrong type for socket", \
        "Protocol not available", \
        "Protocol not supported", \
        "Socket type not supported", \
        "Operation not supported", \
        "Protocol family not supported", \
        "Address family not supported by protocol", \
        "Address already in use", \
        "Cannot assign requested address", \
        "Network is down", \
        "Network is unreachable", \
        "Network dropped connection on reset", \
        "Software caused connection abort", \
        "Connection reset by peer", \
        "No buffer space available", \
        "Socket is already connected", \
        "Socket is not connected", \
        "Cannot send after transport endpoint shutdown", \
        "Too many references: cannot splice", \
        "Connection timed out", \
        "Connection refused", \
        "Host is down", \
        "No route to host", \
        "Operation already in progress", \
        "Operation now in progress", \
        "Stale file handle", \
        "Structure needs cleaning", \
        "Not a XENIX named type file", \
        "No XENIX semaphores available", \
        "Is a named type file", \
        "Remote I/O error", \
        "Quota exceeded", \
        "No medium found", \
        "Wrong medium type", \
        "Operation Canceled", \
        "Identifier removed", \
        "Stream timeout", \
        "Not a stream", \
        "Protocol error", \
        "Multihop attempted", \
        "Link has been severed", \
        "Advertise error", \
        "Srmount error", \
        "Communication error on send", \
        "No such device", \
        "Quorum not present", \
        "Stale NFS file handle", \
        "File locking deadlock", \
        "Too many users", \
        "Socket operation on non-socket", \
        "Destination address required", \
        "Message too long", \
        "Protocol wrong type for socket", \
        "Protocol not available", \
        "Protocol not supported", \
        "Socket type not supported", \
        "Operation not supported", \
        "Protocol family not supported", \
        "Address family not supported by protocol", \
        "Address already in use", \
        "Cannot assign requested address", \
        "Network is down", \
        "Network is unreachable", \
        "Network dropped connection on reset", \
        "Software caused connection abort", \
        "Connection reset by peer", \
        "No buffer space available", \
        "Socket is already connected", \
        "Socket is not connected", \
        "Cannot send after transport endpoint shutdown", \
        "Too many references: cannot splice", \
        "Connection timed out", \
        "Connection refused", \
        "Host is down", \
        "No route to host", \
        "Operation already in progress", \
        "Operation now in progress", \
        "Memory page has hardware error" \
    }

#else
    #error "Unsupported OS"
#endif

#endif
