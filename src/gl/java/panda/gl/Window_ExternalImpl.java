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
    public void initialize_panda$core$String_Int32_Int32_Int32_Int32(panda.gl.Window self, panda.core.String title, int x, int y, int width, int height) {
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
                        panda.gl.events.KeyEvent.createnew$init_panda$gl$events$EventType_panda$gl$events$Key_Int16(
                            panda.gl.events.EventType.$KEYDOWN,
                            getKey(e.getKeyCode()),
                            (short) 0);
                self.$eventQueue.post_panda$gl$events$Event(event);
            }

            public void keyReleased(java.awt.event.KeyEvent e) {
                panda.gl.events.KeyEvent event = 
                        panda.gl.events.KeyEvent.createnew$init_panda$gl$events$EventType_panda$gl$events$Key_Int16(
                            panda.gl.events.EventType.$KEYUP,
                            getKey(e.getKeyCode()),
                            (short) 0);
                self.$eventQueue.post_panda$gl$events$Event(event);
            }
        });

        frame.addMouseMotionListener(new java.awt.event.MouseMotionListener() {
            public void mouseMoved(java.awt.event.MouseEvent e) {
                panda.gl.events.MouseMotionEvent event = 
                        panda.gl.events.MouseMotionEvent.createnew$init_panda$gl$events$EventType_panda$gl$Point(
                            panda.gl.events.EventType.$MOUSEMOTION,
                            panda.gl.Point.createnew$init_Real64_Real64(e.getX(),
                                    e.getY()));
                self.$eventQueue.post_panda$gl$events$Event(event);
            }

            public void mouseDragged(java.awt.event.MouseEvent e) {
                panda.gl.events.MouseMotionEvent event = 
                        panda.gl.events.MouseMotionEvent.createnew$init_panda$gl$events$EventType_panda$gl$Point(
                            panda.gl.events.EventType.$MOUSEMOTION,
                            panda.gl.Point.createnew$init_Real64_Real64(e.getX(),
                                    e.getY()));
                self.$eventQueue.post_panda$gl$events$Event(event);
            }
        });

        frame.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent e) {
                panda.gl.events.MouseEvent event = 
                        panda.gl.events.MouseEvent.createnew$init_panda$gl$events$EventType_Int8_panda$gl$Point(
                            panda.gl.events.EventType.$MOUSEDOWN,
                            (byte) e.getButton(),
                            panda.gl.Point.createnew$init_Real64_Real64(e.getX(),
                                    e.getY()));
                self.$eventQueue.post_panda$gl$events$Event(event);
            }

            public void mouseReleased(java.awt.event.MouseEvent e) {
                panda.gl.events.MouseEvent event = 
                        panda.gl.events.MouseEvent.createnew$init_panda$gl$events$EventType_Int8_panda$gl$Point(
                            panda.gl.events.EventType.$MOUSEUP,
                            (byte) e.getButton(),
                            panda.gl.Point.createnew$init_Real64_Real64(e.getX(),
                                    e.getY()));
                self.$eventQueue.post_panda$gl$events$Event(event);
            }
        });

        self.$native = impl;
    }

    @Override
    public panda.gl.Renderer createRenderer_$Rpanda$gl$Renderer(panda.gl.Window self) {
        panda.gl.Renderer result = panda.gl.Renderer.createnew$init();
        result.$native = new RendererImpl((WindowImpl) self.$native);
        return result;
    }

    void init() {
        panda.gl.events.EventType.$classInit_class();
        panda.gl.events.Key.$classInit_class();
    }

    @Override
    public void startRenderLoop_$LPpanda$core$Real64$RP$EQ$AM$GT$LP$RP(panda.gl.Window window, 
            panda.methods.panda$core$Real64 m) {
        for (;;) {
            m.raw(16.66);
            panda.threads.Thread.sleep_class_Int32(1000 / 60);
        }
    }

    @Override
    public void close(panda.gl.Window self) {
    }
}
