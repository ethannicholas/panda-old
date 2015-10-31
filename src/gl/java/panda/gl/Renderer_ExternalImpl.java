package panda.gl;

/**
 * This was written simply to get pixels on the screen as easily as possible,
 * and certainly is not the best way to do that. Badly in need of optimization.
 */
class Renderer_ExternalImpl implements panda.gl.Renderer_External {
    private long lastPresent;
    private static final int FRAME_MILLIS = 1000 / 60;

/*    @Override
    public panda.gl.Texture loadTexture(panda.gl.Renderer self, panda.io.File path) {
        try {
            panda.gl.Texture result = panda.gl.Texture.createnew$init();
            java.awt.image.BufferedImage img = javax.imageio.ImageIO.read(
                    new java.io.File(panda.core.PandaCore.toJavaString(
                        path.$path)));
            result.$native = img;
            result.$width = img.getWidth();
            result.$height = img.getHeight();
            return result;
        }
        catch (java.io.IOException e) {
            throw new RuntimeException(e);
        }
    }*/

    WindowImpl getWindow(panda.gl.Renderer self) {
        return ((panda.gl.RendererImpl) self.$native).window;
    }

    @Override
    public void setPaint_panda$gl$Paint(panda.gl.Renderer renderer, panda.gl.Paint paint) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void setTransform_panda$gl$Transform(panda.gl.Renderer renderer, panda.gl.Transform transform) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void _save(panda.gl.Renderer renderer) {
    }

    @Override
    public void _restore(panda.gl.Renderer renderer) {
    }

    @Override
    public void clip_panda$gl$shapes$Shape(panda.gl.Renderer renderer, panda.gl.shapes.Shape shape) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void fill_panda$gl$shapes$Shape(panda.gl.Renderer renderer, panda.gl.shapes.Shape shape) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void stroke_panda$gl$shapes$Shape(panda.gl.Renderer renderer, panda.gl.shapes.Shape shape) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void drawImage_panda$gl$images$Image_panda$gl$shapes$Rectangle(panda.gl.Renderer renderer, 
            panda.gl.images.Image image,
            panda.gl.shapes.Rectangle dest) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void clear(panda.gl.Renderer self) {
        WindowImpl impl = getWindow(self);
        impl.graphics.fillRect(0, 0, impl.width, impl.height);
    }

    @Override
    public void present(panda.gl.Renderer self) {
        WindowImpl window = getWindow(self);
        synchronized (window.buffer) {
            window.frame.getContentPane().repaint();
            try {
                window.buffer.wait();
            }
            catch (InterruptedException e) {
            }
        }
        long current = System.currentTimeMillis();
        if (lastPresent != 0) {
            int delta = (int) (current - lastPresent);
            if (delta < FRAME_MILLIS)
                panda.threads.Thread.sleep_class_Int32(FRAME_MILLIS - delta);
        }
        lastPresent = current;
    }

    @Override
    public void close(panda.gl.Renderer self) {
    }
}
