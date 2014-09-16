Threads
=======

A *thread* is an independent stream of execution. A complete program may consist
of many threads, all running different code at the same time.

Threads are created by the [Thread.start()](api/panda/threads/Thread.html#start((\)=&>*(\)\):panda.threads.Thread) 
method, passing in the method to run in the background. The method will run
asynchronously in a separate system thread.

Example:

@SOURCE(
    class ThreadExample {
        @class
        method count() {
            for i in 0 .. 1000000000
                Console.writeLine(i)
        }

        @class
        method doOtherThings() {
            -*REPLACE:...*---dummy comment
        }

        @class
        method main() {
            Thread.start(ThreadExample::count)
            -- we have now started counting in the background, but we can keep 
            -- doing things in the foreground
            doOtherThings()
        }
    }
)

Threads communicate with each other by passing messages using
[`MessageQueue`s](api/panda/threads/MessageQueue.html). Normally, threads may
only exchange [immutable](immutable.html) data. Combined with the fact that
there is no global mutable state, this means that under normal circumstances
threads may not see each other's mutable data and therefore there is no need
for mutexes, semaphores, or other synchronization constructs. 

There are two situations in which threads may exchange mutable data:

* By calling [MessageQueue.postAndExit()](api/panda/threads/MessageQueue.html#postAndExit(panda.core.Object?\)).
  This allows a program to send one mutable object to another thread, and then
  promptly exit. This does not violate any safety rules, because the mutable
  object remains visible to only one thread.
* By calling [MessageQueue.postUnsafe()](api/panda/threads/MessageQueue.html#postUnsafe(panda.core.Object?\)).
  `postUnsafe()` bypasses Panda's normal safety rules and allows mutable data to
  be shared between multiple threads. [panda.threads.Lock](api/panda/threads/Lock.html),
  which is only necessary when `postUnsafe()` has been used, allows threads to 
  cooperate safely with mutable data.