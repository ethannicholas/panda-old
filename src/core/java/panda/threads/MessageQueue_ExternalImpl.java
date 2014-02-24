package panda.threads;

class MessageQueue_ExternalImpl implements panda.threads.MessageQueue_External {
    @Override
    public int pendingMessages(panda.threads.MessageQueue self) {
        java.util.Queue<panda.threads.Message> queue = ((java.util.ArrayDeque<panda.threads.Message>) self.$nativeQueue);
        synchronized (queue) {
            return queue.size();
        }
    }

    @Override
    public panda.core.Object getMessage(panda.threads.MessageQueue self) {
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
    public panda.core.Object getMessage(panda.threads.MessageQueue self, int timeout) {
        return getMessage(self);
    }

    @Override
    public void $finalize(panda.threads.MessageQueue self) {
    }

    @Override
    public void initMessageQueue(panda.threads.MessageQueue self) {
        self.$nativeQueue = 
                new java.util.ArrayDeque<panda.threads.Message>();
    }

    @Override
    public void sendMessage(panda.threads.MessageQueue self, panda.threads.Message message) {
        java.util.Queue<panda.threads.Message> queue = ((java.util.ArrayDeque<panda.threads.Message>) self.$nativeQueue);
        synchronized (queue) {
            queue.add(message);
            queue.notify();
        }
    }

    @Override
    public void threadExit() {
        throw new UnsupportedOperationException();
    }
}
