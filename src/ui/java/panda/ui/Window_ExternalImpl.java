package panda.ui;

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

class Window_ExternalImpl implements panda.ui.Window_External {
    private panda.ui.events.Key getKey(int keyCode) {
        switch (keyCode) {
            case VK_A: return panda.ui.events.Key.$A;
            case VK_D: return panda.ui.events.Key.$D;
            case VK_X: return panda.ui.events.Key.$X;
            case VK_Z: return panda.ui.events.Key.$Z;
            case VK_ESCAPE: return panda.ui.events.Key.$ESCAPE;
            case VK_SPACE: return panda.ui.events.Key.$SPACE;
            case VK_DOWN: return panda.ui.events.Key.$DOWN;
            case VK_LEFT: return panda.ui.events.Key.$LEFT;
            case VK_RIGHT: return panda.ui.events.Key.$RIGHT;
            case VK_UP: return panda.ui.events.Key.$UP;
            default: return panda.ui.events.Key.$UNKNOWN;
        }
    }

    @Override
    public void initialize_panda$core$String_Int32_Int32_Int32_Int32(panda.ui.Window self, panda.core.String title, int x, int y, int width, int height) {
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
                panda.ui.events.KeyEvent event = 
                        panda.ui.events.KeyEvent.createnew$init_panda$ui$events$EventType_panda$ui$events$Key_Int16(
                            panda.ui.events.EventType.$KEYDOWN,
                            getKey(e.getKeyCode()),
                            (short) 0);
                self.$eventQueue.post_panda$core$Immutable(event);
            }

            public void keyReleased(java.awt.event.KeyEvent e) {
                panda.ui.events.KeyEvent event = 
                        panda.ui.events.KeyEvent.createnew$init_panda$ui$events$EventType_panda$ui$events$Key_Int16(
                            panda.ui.events.EventType.$KEYUP,
                            getKey(e.getKeyCode()),
                            (short) 0);
                self.$eventQueue.post_panda$core$Immutable(event);
            }
        });

        frame.addMouseMotionListener(new java.awt.event.MouseMotionListener() {
            public void mouseMoved(java.awt.event.MouseEvent e) {
                panda.ui.events.MouseMotionEvent event = 
                        panda.ui.events.MouseMotionEvent.createnew$init_panda$ui$events$EventType_Int32_Int32(
                            panda.ui.events.EventType.$MOUSEMOTION, e.getX(),
                            e.getY());
                self.$eventQueue.post_panda$core$Immutable(event);
            }

            public void mouseDragged(java.awt.event.MouseEvent e) {
                panda.ui.events.MouseMotionEvent event = 
                        panda.ui.events.MouseMotionEvent.createnew$init_panda$ui$events$EventType_Int32_Int32(
                            panda.ui.events.EventType.$MOUSEMOTION, e.getX(),
                            e.getY());
                self.$eventQueue.post_panda$core$Immutable(event);
            }
        });

        frame.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent e) {
                panda.ui.events.MouseEvent event = 
                        panda.ui.events.MouseEvent.createnew$init_panda$ui$events$EventType_Int8_Int32_Int32(
                            panda.ui.events.EventType.$MOUSEDOWN,
                            (byte) e.getButton(), e.getX(), e.getY());
                self.$eventQueue.post_panda$core$Immutable(event);
            }

            public void mouseReleased(java.awt.event.MouseEvent e) {
                panda.ui.events.MouseEvent event = 
                        panda.ui.events.MouseEvent.createnew$init_panda$ui$events$EventType_Int8_Int32_Int32(
                            panda.ui.events.EventType.$MOUSEUP,
                            (byte) e.getButton(), e.getX(), e.getY());
                self.$eventQueue.post_panda$core$Immutable(event);
            }
        });

        self.$native = impl;
    }

    void init() {
        panda.ui.events.EventType.$classInit_class();
        panda.ui.events.Key.$classInit_class();
    }

    @Override
    public void close(panda.ui.Window self) {
    }
}
