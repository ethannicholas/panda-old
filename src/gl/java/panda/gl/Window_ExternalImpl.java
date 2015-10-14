package panda.gl;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.Transparency;
import java.awt.image.BufferedImage;
import javax.swing.JComponent;
import javax.swing.JFrame;
import panda.core.PandaCore;
import static java.awt.event.KeyEvent.*;

class WindowImpl {
    JFrame frame;
    int width;
    int height;
    BufferedImage buffer;
    Graphics2D graphics;
}

class Window_ExternalImpl implements panda.gl.Window_External {
    private panda.gl.events.Key getKey(int keyCode) {
        switch (keyCode) {
            case VK_A: return panda.gl.events.Key.$A;
            case VK_D: return panda.gl.events.Key.$D;
            case VK_X: return panda.gl.events.Key.$X;
            case VK_Z: return panda.gl.events.Key.$Z;
            case VK_ESCAPE: return panda.gl.events.Key.$ESCAPE;
            case VK_SPACE: return panda.gl.events.Key.$SPACE;
            case VK_DOWN: return panda.gl.events.Key.$DOWN;
            case VK_LEFT: return panda.gl.events.Key.$LEFT;
            case VK_RIGHT: return panda.gl.events.Key.$RIGHT;
            case VK_UP: return panda.gl.events.Key.$UP;
            default: return panda.gl.events.Key.$UNKNOWN;
        }
    }

    @Override
    public void init(panda.gl.Window self, panda.core.String title, int x, int y, int width, int height) {
        init();
        final WindowImpl impl = new WindowImpl();

        JFrame frame = new JFrame(PandaCore.toJavaString(title));
        impl.frame = frame;
        impl.width = width;
        impl.height = height;

        GraphicsConfiguration gc = GraphicsEnvironment.
                getLocalGraphicsEnvironment().
                getDefaultScreenDevice().
                getDefaultConfiguration();

        impl.buffer = gc.createCompatibleImage(width, height, 
                Transparency.OPAQUE);

        impl.graphics = impl.buffer.createGraphics();

        frame.setContentPane(new JComponent() {
            public void paintComponent(Graphics g) {
                synchronized (impl.buffer) {
                    g.drawImage(impl.buffer, 0, 0, null);
                    impl.buffer.notify();
                }
            }
        });
        frame.getContentPane().setPreferredSize(new Dimension(width, height));
        frame.pack();
        frame.setVisible(true);

        frame.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent e) {
                panda.gl.events.KeyEvent event = 
                        panda.gl.events.KeyEvent.createnew$init(
                            panda.gl.events.EventType.$KEYDOWN,
                            getKey(e.getKeyCode()),
                            (short) 0);
                self.$eventQueue.post(event);
            }

            public void keyReleased(java.awt.event.KeyEvent e) {
                panda.gl.events.KeyEvent event = 
                        panda.gl.events.KeyEvent.createnew$init(
                            panda.gl.events.EventType.$KEYUP,
                            getKey(e.getKeyCode()),
                            (short) 0);
                self.$eventQueue.post(event);
            }
        });

        frame.addMouseMotionListener(new java.awt.event.MouseMotionListener() {
            public void mouseMoved(java.awt.event.MouseEvent e) {
                panda.gl.events.MouseMotionEvent event = 
                        panda.gl.events.MouseMotionEvent.createnew$init(
                            panda.gl.events.EventType.$MOUSEMOTION,
                            panda.gl.Point.createnew$init(e.getX(),
                                    e.getY()));
                self.$eventQueue.post(event);
            }

            public void mouseDragged(java.awt.event.MouseEvent e) {
                panda.gl.events.MouseMotionEvent event = 
                        panda.gl.events.MouseMotionEvent.createnew$init(
                            panda.gl.events.EventType.$MOUSEMOTION,
                            panda.gl.Point.createnew$init(e.getX(),
                                    e.getY()));
                self.$eventQueue.post(event);
            }
        });

        frame.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent e) {
                panda.gl.events.MouseEvent event = 
                        panda.gl.events.MouseEvent.createnew$init(
                            panda.gl.events.EventType.$MOUSEDOWN,
                            (byte) e.getButton(),
                            panda.gl.Point.createnew$init(e.getX(),
                                    e.getY()));
                self.$eventQueue.post(event);
            }

            public void mouseReleased(java.awt.event.MouseEvent e) {
                panda.gl.events.MouseEvent event = 
                        panda.gl.events.MouseEvent.createnew$init(
                            panda.gl.events.EventType.$MOUSEUP,
                            (byte) e.getButton(),
                            panda.gl.Point.createnew$init(e.getX(),
                                    e.getY()));
                self.$eventQueue.post(event);
            }
        });

        self.$native = impl;
    }

    @Override
    public panda.gl.Renderer createRenderer(panda.gl.Window self) {
        panda.gl.Renderer result = panda.gl.Renderer.createnew$init();
        result.$native = new RendererImpl((WindowImpl) self.$native);
        return result;
    }

    void init() {
        panda.gl.events.EventType.$classInit();
        panda.gl.events.Key.$classInit();
    }

    @Override
    public void startRenderLoop(panda.gl.Window window, 
            panda.core.MutableMethod m) {
        try {
            for (;;) {
                if (true)
                    throw new UnsupportedOperationException();
//                ((panda.methods.$nullary) m.$rawPtr).method();
                Thread.sleep(1000 / 60);
            }
        }
        catch (InterruptedException e) {
        }
    }

    @Override
    public void close(panda.gl.Window self) {
    }
}
