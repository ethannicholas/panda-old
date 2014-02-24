Threads
=======

A *thread* is an independent stream of execution. A complete program may consist
of many threads, all running different code at the same time.

Threads are created by subclassing the class 
[`panda.threads.Thread`](api/panda.threads.Thread.html) and overriding the
`run()` method. Create an instance of your `Thread` subclass and call 
`thread.start()` in order to start up a new thread. The thread object will then 
call its overridden `run()` method in a separate operating-system level thread.

Example:

    class CountingThread {
        @override
        method run() {
            for i := 0 to 1000000000
                Console.writeLine(i)
        }
    }

    new CountingThread().start()
    -- we have now started counting in the background, but we can keep doing
    -- things in the foreground
    doOtherThings()

Threads communicate with each other by passing messages using
[`MessageQueue`s](api/panda.threads.MessageQueue.html). Normally, threads may
only exchange [immutable](immutable.html) data. Combined with the fact that
there is no global mutable state, this means that under normal circumstances
threads may not see each other's mutable data and therefore there is no need
for mutexes, semaphores, or other synchronization constructs. 

There are two situations in which threads may exchange mutable data:

* By calling [MessageQueue.postAndExit()](api/panda.threads.MessageQueue.html#postAndExit%28data:panda.core.Object%63%29).
  This allows a program to send one mutable object to another thread, and then
  promptly exit. This does not violate any safety rules, because the mutable
  object remains visible to only one thread.
* By calling [MessageQueue.postUnsafe()](api/panda.threads.MessageQueue.html#postUnsafe%28data:panda.core.Object%63%29).
  `postUnsafe()` bypasses Panda's normal safety rules and allows mutable data to
  be shared between multiple threads. [panda.threads.Lock](api/panda.threads.Lock.html),
  which is only necessary when `postUnsafe()` has been used, allows threads to 
  cooperate safely with mutable data.