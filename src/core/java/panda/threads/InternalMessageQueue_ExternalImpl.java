package panda.threads;

class InternalMessageQueue_ExternalImpl implements panda.threads.InternalMessageQueue_External {
    @Override
    public long pendingMessages_$Rpanda$core$Int64(panda.threads.InternalMessageQueue self) {
        java.util.Queue<panda.threads.Message> queue = ((java.util.ArrayDeque<panda.threads.Message>) self.$nativeQueue);
        synchronized (queue) {
            return queue.size();
        }
    }

    @Override
    public panda.core.Object getMessage_$Rpanda$core$Object$Z(panda.threads.InternalMessageQueue self) {
        java.util.Queue<panda.threads.Message> queue = ((java.util.ArrayDeque<panda.threads.Message>) self.$nativeQueue);
        synchronized (queue) {
            while (queue.isEmpty()) {
                try {
                    queue.wait();
                }
                catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
            return queue.remove().$data;
        }
    }

    @Override
    public panda.core.Object getMessage_Int64_$Rpanda$core$Object$Z(panda.threads.InternalMessageQueue self, long timeout) {
        return getMessage_$Rpanda$core$Object$Z(self);
    }

    @Override
    public void $finalize(panda.threads.InternalMessageQueue self) {
    }

    @Override
    public void initMessageQueue(panda.threads.InternalMessageQueue self) {
        self.$nativeQueue = 
                new java.util.ArrayDeque<panda.threads.Message>();
    }

    @Override
    public void sendMessage_panda$threads$Message(panda.threads.InternalMessageQueue self, panda.threads.Message message) {
        java.util.Queue<panda.threads.Message> queue = ((java.util.ArrayDeque<panda.threads.Message>) self.$nativeQueue);
        synchronized (queue) {
            queue.add(message);
            queue.notify();
        }
    }

    @Override
    public void threadExit_class() {
        throw new UnsupportedOperationException();
    }
}
