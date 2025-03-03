This project is a simple client server communication system implemented using signals in C.
The client sends a message to the server, and the server receive and display the message character by character


# How does Minitalk Work :
the communication between client and server is done using UNIX signals.
# What are unix signals? :
[[mini_talk.canvas|mini_talk]]

before diving into Unix signals lets explore what is signals in general :
Signals are software interrupts sent to a process (a running program) by the operating system

in summary :
Process is a running program.
Signal : is a notification sent to the process (SIGUSR1).
Handler : code that runs in response to the signal.

# Types of Signals :
*  A-  Standard signals 
Predefined by the OS ex :
	- SIGINT (interrupt) : Sent when you press Ctrl+C -> terminate the process.
	- SIGSEGV (Segmentation Violation) : Sent when a program access an invalid memory -> leads to crashes the process.
	- SIGKILL : Forcefully terminate a process (cannot be ignored or handled).
* B- Real Time Signals 
eg : SIGRTMIN SIGRTMAX
	- They can carry data.
	- used for advanced inter-process communication (IPC);.

*SIGSEGV   is triggered when the CPU detects an invalid memory access.
The OS Kernel converts hardware exceptions into signals (like SIGSEGV).
processes crash by default to prevent undefined behavior*
# UNIX SIGNALS (Focus on SIGUSR1  and SIGUSR2)

for minitalk project, i will use two user-defined signals:
	*SIGUSR1* (user signal 1) : Reserved for costume use.
	*SIGUSR2*(user signal 2) : Reserved for costume use.

Why these?
- they have no predefined meaning in UNIX -> you assign them your own logic (eg, SIGUSR1 = bit 0, SIGUSR2 = bit 1); 
# NOW How UNIX Signals Works

						-------Lifecycle of a signal------- 
1- Generation : 
- A signal is created by the OS, a process, or hardware).
- Example : Client sends SIGUSR1 To the server.
2- Delivery :
- The signal is delivered to the target process.
- The OS checks if the process is allowed to receive it (permissions , PID validity).
3- Handling :
- the process reacts to signal by either :
	- Default action (eg, terminate, ignore).
	- Custom handler : A function you define (eg, collect bits for minitalk).
	- Ignoring the signal (if allowed, eg, SIGUSR1 can be ignored).

# Signal Masking 
- Process can block certain signals temporarily.
- Blocked signals are pending until unblocked (but still not queued).
#example A server might block signals while reconstructing a byte to avoid corruption 

# Challenges with Signals
- Signal Loss
	- if signals are sent too quickly, some may be lost.
	- Solution : Synchronize communication (eg, clients wait fo an acknowledgement from the server before sending the next bit).
# How minitalk Use UNIX Signals
## 1- Server Setup : 
- The server registers handlers for SIGUSR1 and SIGUSR2.
- it enter an infinite loop, waiting for signals.
## 2- Client communication :
- The client send a sequence of SIGUSR1 (0) and SIGUSR2 (1) signals to the server's PID.
- Each signal represents a bit in a binary message (eg, 01000001= 'A').
## 3- Server Processing :
- The server's handler collects bits into a buffer.
- one 8 bits are received, it converts them into character and prints it.



# -----------Functions in the Subject-----------

# 1-Signal vs Sigaction
- Purpose : Both set up signal handlers (functions to run when a signal arrives).
- *Key differences :*
	- signal() : Simpler but less control (cant block signals during handling).
	- sigaction() : More powerful lets you:
		- specify a handler function.
		- Block other signals while handling the current one (using sigemptyset/sigaddset).
		- Set flags (restart interrupted system calls).
	I will use sigaction to handle SIGUSR1 and SIGUSR2
# 2-Sigemptyset & sigaddset
- *Purpose :*
	- Manipulate signal sets (collections of signals to block/allow).
- *How they work :*
	- sigemptyset (&set) : initialize a signal set to be empty.
	- sigaddset(&set, SIGUSR1) : dd SIGUSR1 to the set.
- *USE CASE :*
	- When handling a signal (eg SIGUSR1), you might want to block other signals(like SIGUSR2) temporarily to avoid interruptions.
# 3-Kill
- *Purpose :*
	- Send a signal to a process.
- *Syntaxe :*
	- kill(pid, signal_type) eg kill(12334, SIGUSR1).
- *Key Notes :*
	- The client use this to send bits(SIGUSR1=0, SIGUSR2=1) to the servers's PID.
	- Permission : You can only send signals to processes you own (unless you're root).
- Minitalk Use :
	- Client sends signals to the server's PID.
# 4-Getpid :
- *Purpose :*
	- get the Process ID  of the current process.
- *Minitalk Use :*
	- The server calls get_pid() to display its Pid (so the client knows where to send the signal).
# 5-Pause
- *Purpose :*
	- Pause the process until a signal arrives.
- *Minitalk Use :*
	- The server runs pause() in a loop to wait indefinitely for signals.
	- when a signal arrives, the handler runs, and pause() resumes waiting afterward.
# 6-Sleep & uSleep
- *Purpose :*
	- Delay execution for a specified time.
	- sleep(2) : sleep for 2 seconds.
	- usleep(100) : sleep for 100 microseconds.
- *Minitalk Use :*
	- Client : Slow down signal sending to avoid overlapping.



# How Thew Work Together in MiniTalk

### *Server Workflow :*
1 - getpid() -> Display PID.
2- sigaction() -> Set up handlers for SIGUSR1/SIGUSR2.
3- pause() in a loop to wait for signals.
### Client Workflow :
1- Parse the server's PID and message.
2-Convert each character to 8 bits.
3- Use kill() to send SIGUSR1/SIGUSR2 for each bit.
4-Use usleep() (temporarily ) to avoid signal loss.


#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
# The Low Level of Signals

Signals a software interrupts, They are used to notify processes of events, like errors or user actions, For when you press Ctrl +C it send a signal SIGINT to terminate a process.
## But how exactly this work under the hood ? 


we will talk about : the lifecycle : generation, delivery,  handling, then get into the kernel's role, data structures involved, and CPU interaction.
When a signal is generated, it's sent to a process. The kerne checks permissions. does sending process have the right to send that signal?
For example : a regular user can't send signals to another user's processes unless they have permission.
Then the signal is pending until the target process is scheduled. The kernel sets a bit in the process's pending signal mask

#### But how the kernel actually interrupt the process?
When a process is running in user mode, the kernel can't immediately interrupt it unless there is a context switch. so signals re checked when returning from kernel mode to user mode .
##### For example: 
after a system call or an interrupt. The kernel will check the pending signals and deliver them before resuming user mode

###  - *Mode Switch : The CPU switch between user mode and kernel mode to handle system calls, exceptions or interrupts*
###  - *Context Switch : The Cpu switches from one process to anoother to allow multitasking.