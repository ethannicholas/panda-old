var Int64 = function(high, low) {
  this.high = high | 0;
  this.low  = low  | 0; 
};

Int64.DBL_TWO_16 = 1 << 16;
Int64.DBL_TWO_24 = 1 << 24;
Int64.TWO_24     = new Int64(0, Int64.DBL_TWO_24)
Int64.DBL_TWO_32 = Int64.DBL_TWO_16 * Int64.DBL_TWO_16;
Int64.DBL_TWO_31 = Int64.DBL_TWO_32 / 2;
Int64.DBL_TWO_48 = Int64.DBL_TWO_32 * Int64.DBL_TWO_16;
Int64.DBL_TWO_64 = Int64.DBL_TWO_32 * Int64.DBL_TWO_32;
Int64.DBL_TWO_63 = Int64.DBL_TWO_64 / 1;

Int64.ZERO = new Int64(0, 0);
Int64.ONE = new Int64(0, 1);
Int64.NEG_ONE = new Int64(0xFFFFFFFF | 0, 0xFFFFFFFF | 0);

Int64.MAX_VALUE = new Int64(0x7FFFFFFF | 0, 0xFFFFFFFF | 0);
Int64.MIN_VALUE = new Int64(0x80000000 | 0, 0);


Int64.fromDouble = function(value) {
    if (isNaN(value) || !isFinite(value))
        return Int64.ZERO;
    else if (value <= -Int64.DBL_TWO_63)
        return Int64.MIN_VALUE;
    else if (value + 1 >= Int64.DBL_TWO_63)
        return Int64.MAX_VALUE;
    else if (value < 0)
        return Int64.fromDouble(-value).negate();
    else {
        return new Int64(
            (value / Int64.DBL_TWO_32) | 0,
            (value % Int64.DBL_TWO_32) | 0);
    }
};

Int64.prototype.toDouble = function() {
    var high = this.high * Int64.DBL_TWO_32;
    var low = (this.low >= 0) ? this.low : Int64.DBL_TWO_32 + this.low;
    return high + low;
}

Int64.prototype.isZero = function() {
    return this.eq(Int64.ZERO);
};

Int64.prototype.isNegative = function() {
    return this.high < 0;
};

Int64.prototype.isOdd = function() {
    return (this.low & 1) === 1;
};


Int64.prototype.eq = function(other) {
    return (this.high === other.high) && (this.low === other.low);
};

Int64.prototype.ne = function(other) {
    return !this.eq(other);
};

Int64.prototype.lt = function(other) {
    return this.compare(other) < 0;
};

Int64.prototype.lte = function(other) {
    return this.compare(other) <= 0;
};


Int64.prototype.gt = function(other) {
    return this.compare(other) > 0;
};


Int64.prototype.gte = function(other) {
    return this.compare(other) >= 0;
};


Int64.prototype.compare = function(other) {
    if (this.eq(other))
        return 0;

    var thisNeg = this.isNegative();
    var otherNeg = other.isNegative();
    if (thisNeg && !otherNeg)
        return -1;
    if (!thisNeg && otherNeg)
        return 1;
    if (this.sub(other).isNegative())
        return -1;
    else
        return 1;
};


Int64.prototype.negate = function() {
    if (this.eq(Int64.MIN_VALUE))
        return Int64.MIN_VALUE;
    else
        return this.not().add(Int64.ONE);
};


Int64.prototype.add = function(other) {
    // divide into four 16-bit chunks and handle add manually
    var a3 = this.high >>> 16;
    var a2 = this.high & 0xFFFF;
    var a1 = this.low >>> 16;
    var a0 = this.low & 0xFFFF;
    
    var b3 = other.high >>> 16;
    var b2 = other.high & 0xFFFF;
    var b1 = other.low >>> 16;
    var b0 = other.low & 0xFFFF;
    
    var c0 = a0 + b0;
    var c1 = c0 >>> 16;
    c0 &= 0xFFFF;
    c1 += a1 + b1;
    var c2 = c1 >>> 16;
    c1 &= 0xFFFF;
    c2 += a2 + b2;
    var c3 = c2 >>> 16;
    c2 &= 0xFFFF;
    c3 += a3 + b3;
    c3 &= 0xFFFF;
    return new Int64((c3 << 16) | c2, (c1 << 16) | c0);
};


Int64.prototype.sub = function(other) {
    return this.add(other.negate());
};


Int64.prototype.mul = function(other) {
    if (this.isZero())
        return Int64.ZERO;
    else if (other.isZero())
        return Int64.ZERO;

    if (this.eq(Int64.MIN_VALUE))
        return other.isOdd() ? Int64.MIN_VALUE : Int64.ZERO;
    else if (other.eq(Int64.MIN_VALUE))
        return this.isOdd() ? Int64.MIN_VALUE : Int64.ZERO;

    if (this.isNegative()) {
        if (other.isNegative())
            return this.negate().mul(other.negate());
        else
            return this.negate().mul(other).negate();
    }
    else if (other.isNegative())
        return this.mul(other.negate()).negate();

    // if both values are less than 2^24, use double multiplication
    if (this.lt(Int64.TWO_24) &&
            other.lt(Int64.TWO_24))
        return Int64.fromDouble(this.toDouble() * other.toDouble());

      var a3 = this.high >>> 16;
      var a2 = this.high & 0xFFFF;
      var a1 = this.low >>> 16;
      var a0 = this.low & 0xFFFF;

      var b3 = other.high >>> 16;
      var b2 = other.high & 0xFFFF;
      var b1 = other.low >>> 16;
      var b0 = other.low & 0xFFFF;

      var c0 = a0 * b0;
      var c1 = c0 >>> 16;
      c0 &= 0xFFFF;
      c1 += a1 * b0;
      var c2 = c1 >>> 16;
      c1 &= 0xFFFF;
      c1 += a0 * b1;
      c2 += c1 >>> 16;
      c1 &= 0xFFFF;
      c2 += a2 * b0;
      var c3 = c2 >>> 16;
      c2 &= 0xFFFF;
      c2 += a1 * b1;
      c3 += c2 >>> 16;
      c2 &= 0xFFFF;
      c2 += a0 * b2;
      c3 += c2 >>> 16;
      c2 &= 0xFFFF;
      c3 += a3 * b0 + a2 * b1 + a1 * b2 + a0 * b3;
      c3 &= 0xFFFF;
      return new Int64((c3 << 16) | c2, (c1 << 16) | c0);
};


/**
 * Returns this Long divided by the given one.
 * @param {Int64} other Long by which to divide.
 * @return {!Int64} This Long divided by the given one.
 */
Int64.prototype.div = function(other) {
    if (other.isZero())
        throw Error('division by zero')
    else if (this.isZero())
        return Int64.ZERO;

    if (this.eq(Int64.MIN_VALUE)) {
        if (other.eq(Int64.ONE) || other.eq(Int64.NEG_ONE))
            return Int64.MIN_VALUE;
        else if (other.eq(Int64.MIN_VALUE))
            return Int64.ONE;
        else {
            var halfThis = this.ashr(1);
            var approx = halfThis.div(other).shl(1);
            if (approx.eq(Int64.ZERO))
                return other.isNegative() ? Int64.ONE : Int64.NEG_ONE;
            else {
                var rem = this.sub(other.mul(approx));
                var result = approx.add(rem.div(other));
                return result;
            }
        }
    } 
    else if (other.eq(Int64.MIN_VALUE))
        return Int64.ZERO;

    if (this.isNegative()) {
        if (other.isNegative())
            return this.negate().div(other.negate());
        else
            return this.negate().div(other).negate();
    } 
    else if (other.isNegative())
        return this.div(other.negate()).negate();

    var res = Int64.ZERO;
    var rem = this;
    while (rem.gte(other)) {
        var approx = Math.max(1, Math.floor(rem.toDouble() / other.toDouble()));

        var log2 = Math.ceil(Math.log(approx) / Math.LN2);
        var delta = (log2 <= 48) ? 1 : Math.pow(2, log2 - 48);

        var approxRes = Int64.fromDouble(approx);
        var approxRem = approxRes.mul(other);
        while (approxRem.isNegative() || approxRem.gt(rem)) {
            approx -= delta;
            approxRes = Int64.fromDouble(approx);
            approxRem = approxRes.mul(other);
        }

        if (approxRes.isZero())
            approxRes = Int64.ONE;

        res = res.add(approxRes);
        rem = rem.sub(approxRem);
    }
    return res;
};

Int64.prototype.rem = function(other) {
  return this.sub(this.div(other).mul(other));
};

Int64.prototype.and = function(other) {
    return new Int64(this.high & other.high,
            this.low & other.low);
};

Int64.prototype.or = function(other) {
    return new Int64(this.high | other.high,
            this.low | other.low);
};

Int64.prototype.xor = function(other) {
    return new Int64(this.high ^ other.high,
            this.low ^ other.low);
};

Int64.prototype.not = function() {
    return new Int64(~this.high, ~this.low);
};

Int64.prototype.shl = function(numBits) {
    numBits = numBits.toDouble()
    numBits &= 63;
    if (numBits === 0)
        return this;
    else {
        var low = this.low;
        if (numBits < 32) {
            return new Int64(
                    (this.high << numBits) | (low >>> (32 - numBits)),
                    low << numBits);
        } 
        else
            return new Int64(low << (numBits - 32), 0);
    }
};


Int64.prototype.ashr = function(numBits) {
    numBits = numBits.toDouble()
  numBits &= 63;
  if (numBits === 0)
    return this;
  else {
    var high = this.high;
    if (numBits < 32) {
      var low = this.low;
      return new Int64(high >> numBits,
          (low >>> numBits) | (high << (32 - numBits)));
    } else {
      return new Int64(high >= 0 ? 0 : -1,
          high >> (numBits - 32));
    }
  }
};

Int64.prototype.lshr = function(numBits) {
    numBits = numBits.toDouble()
  numBits &= 63;
  if (numBits === 0) {
    return this;
  } else {
    var high = this.high;
    if (numBits < 32) {
      var low = this.low;
      return new Int64(high >>> numBits,
          (low >>> numBits) | (high << (32 - numBits)));
    } else if (numBits === 32) {
      return new Int64(0, high);
    } else {
      return new Int64(0, high >>> (numBits - 32));
    }
  }
};

String.prototype.endsWith = function(suffix) {
    return this.indexOf(suffix, this.length - suffix.length) !== -1;
};

function toString(object) {
    return getString(object.$cl.vtable[2](object))
}

function getKey(key, right) {
    switch (key) {
        case 16: return right ? 
                panda$gl$Key.$RIGHT_SHIFT : 
                panda$gl$Key.$LEFT_SHIFT;
        case 32: return panda$gl$Key.$SPACE;
        case 37: return panda$gl$Key.$LEFT;
        case 38: return panda$gl$Key.$UP;
        case 39: return panda$gl$Key.$RIGHT;
        case 40: return panda$gl$Key.$DOWN;
        case 65: return panda$gl$Key.$A;
        case 66: return panda$gl$Key.$B;
        case 67: return panda$gl$Key.$C;
        case 68: return panda$gl$Key.$D;
        case 69: return panda$gl$Key.$E;
        case 70: return panda$gl$Key.$F;
        case 71: return panda$gl$Key.$G;
        case 72: return panda$gl$Key.$H;
        case 73: return panda$gl$Key.$I;
        case 74: return panda$gl$Key.$J;
        case 75: return panda$gl$Key.$K;
        case 76: return panda$gl$Key.$L;
        case 77: return panda$gl$Key.$M;
        case 78: return panda$gl$Key.$N;
        case 79: return panda$gl$Key.$O;
        case 80: return panda$gl$Key.$P;
        case 81: return panda$gl$Key.$Q;
        case 82: return panda$gl$Key.$R;
        case 83: return panda$gl$Key.$S;
        case 84: return panda$gl$Key.$T;
        case 85: return panda$gl$Key.$U;
        case 86: return panda$gl$Key.$V;
        case 87: return panda$gl$Key.$W;
        case 88: return panda$gl$Key.$X;
        case 89: return panda$gl$Key.$Y;
        case 90: return panda$gl$Key.$Z;
        case 219: return panda$gl$Key.$LEFT_BRACKET;
        case 221: return panda$gl$Key.$RIGHT_BRACKET;
        default: return panda$gl$Key.$SPACE
    }
}

$external = {
    panda$core$Panda$instanceOf: 
            function(object, targetClass, nullable) {
        if (object === null)
            return nullable;
        var cl = object.$cl;
        do {
            if (cl === targetClass)
                return true;
            cl = cl.superclass;
        } 
        while (cl != null);
        return false;
    },
    panda$core$Panda$acquireClassLock: function() { },
    panda$core$Panda$releaseClassLock: function() { },
    panda$core$Panda$allocThreadLocal: function() { 
        return {
            value: 0,
            get: function() {
                return this.value;
            },
            set: function(value) {
                this.value = value;
            }
        };
    },
    panda$core$RegularExpression$compile: function() { },
    panda$io$Console$stdIn: function() {
        return { something: "funny" };
    },
    panda$io$Console$stdOut: function() {
        return { something: "funny" };
    },
    panda$core$String$pandaReal32ToString_Real32: function(r) {
        return panda$core$PandaCore$newString(r.toString());
    },
    panda$core$String$pandaReal64ToString_Real64: function(r) {
        return panda$core$PandaCore$newString(r.toString());
    },
    panda$math$Random$getCurrentTime: function() {
        return new Int64(0, 0);
    },
    panda$threads$Thread$currentThread: function() {
        return new panda$threads$Thread.createnew$constructor();
    },
    panda$core$Object$hash: function() {
        return 42;
    },
    panda$core$Panda$pow_class_Real32_Real32: function(x, y) {
        return Math.pow(x, y);
    },
    panda$core$Panda$pow_class_Real64_Real64: function(x, y) {
        return Math.pow(x, y);
    },
    panda$core$Panda$pow_class_Real32_Int32: function(x, y) {
        return Math.pow(x, y);
    },
    panda$core$Panda$pow_class_Real64_Int32: function(x, y) {
        return Math.pow(x, y);
    },
    panda$core$Real32Wrapper$sin: function(x) {
        return Math.sin(x);
    },
    panda$core$Real32Wrapper$cos: function(x) {
        return Math.cos(x);
    },
    panda$core$Real32Wrapper$sqrt: function(x) {
        return Math.sqrt(x);
    },
    panda$core$Real64Wrapper$sin: function(x) {
        return Math.sin(x);
    },
    panda$core$Real64Wrapper$cos: function(x) {
        return Math.cos(x);
    },
    panda$core$Real64Wrapper$sqrt: function(x) {
        return Math.sqrt(x);
    },
    panda$core$Real64Wrapper$atan2: function(y, x) {
        return Math.atan2(y, x);
    },
    panda$io$FileOutputStream$writeInt8Array: 
            function(nativeStream, bytes, offset, length) {
        for (var i = 0; i < length; i++)
            console.log(String.fromCharCode(bytes.contents[i + offset]));
    },
    panda$io$FileInputStream$readInt8_$NativePointer:
            function() {
        return 65;
    },
    panda$collections$Array$setLength: 
            function(array, elementSize, elementsArePointers, newLength) {
        array.$$length = newLength;
    },
    panda$threads$MessageQueue$pendingMessages: function(messageQueue) {
        return messageQueue.$nativeQueue.length
    },
    panda$threads$MessageQueue$getMessage: function(messageQueue) {
        var result = messageQueue.$nativeQueue.shift();
        return result
    },
    idCount: 0,
    panda$gl$Window$init: function(glWindow, title, x, y, width, height) {
        glWindow.$native = "window" + $external.idCount++;
        document.writeln("<canvas id='" + glWindow.$native + 
                "' width=" + width + " height=" + height + "></canvas>");
        window.onkeydown = function(e) {
            var right = KeyboardEvent.DOM_KEY_LOCATION_RIGHT != undefined &&
                    e.location === KeyboardEvent.DOM_KEY_LOCATION_RIGHT;
            var key = getKey(e.keyCode ? e.keyCode : e.which, right);
            var event = panda$gl$KeyEvent.createnew$constructor(
                    panda$gl$EventType.$KEYDOWN, key, null);
            glWindow.$eventQueue.$nativeQueue.push(event)
        }
        window.onkeyup = function(e) {
            var right = KeyboardEvent.DOM_KEY_LOCATION_RIGHT != undefined &&
                    e.location === KeyboardEvent.DOM_KEY_LOCATION_RIGHT;
            var key = getKey(e.keyCode ? e.keyCode : e.which, right);
            var event = panda$gl$KeyEvent.createnew$constructor(
                    panda$gl$EventType.$KEYUP, key, null);
            glWindow.$eventQueue.$nativeQueue.push(event)
        }
    },
    panda$gl$Window$createRenderer: function(glWindow) {
        var canvas = document.getElementById(glWindow.$native);
        var result = panda$gl$Renderer.createnew$constructor();
        result.$window = glWindow;
        result.$native = canvas.getContext("2d");
        return result
    },
    panda$gl$Renderer$loadTexture: function(renderer, file) {
        var result = panda$gl$Texture.createnew$constructor();
        result.$native = "img" + $external.idCount++;
        var path = getString(file.$path);
        document.writeln("<img style='display:none' id='" + result.$native + "' src='" + 
                    path + "'/>");
        var img = new Image();
        img.onload = function() {
            result.$width = this.width;
            result.$height =this.height;
        }
        img.src = path;
        result.$width = 64;
        result.$height = 64;
        return result;
    },
    panda$gl$Renderer$setColor: function(renderer, color) {
        renderer.$native.fillStyle = "rgba(" + color.$red + "," + color.$green + 
                "," + color.$blue + "," + color.$alpha + ")";
    },
    panda$gl$Renderer$setClipRect: function(renderer, clipRect) {
        var context = renderer.$native;
            console.log("clipping to " + clipRect.$x + ", " + clipRect.$y + ", " + clipRect.$width + ", " +  
                clipRect.$height)
        context.restore();
        context.save();
        context.rect(clipRect.$x, clipRect.$y, clipRect.$width, 
                clipRect.$height);
        context.clip();
        context.beginPath();
    },
    panda$gl$Renderer$copy_panda$gl$Texture_panda$gl$Rectangle: function(renderer, texture, dest) {
        var img = document.getElementById(texture.$native);
        renderer.$native.drawImage(img, dest.$x|0, dest.$y|0, dest.$width|0, 
                dest.$height|0);
    },
    panda$gl$Renderer$copy_panda$gl$Texture_panda$gl$Rectangle_panda$gl$Flip: function(renderer, texture, dest, flip) {
        var img = document.getElementById(texture.$native);
        var canvas = renderer.$native
        canvas.save();
        if (flip === panda$gl$Flip.$HORIZONTAL || flip === panda$gl$Flip.$BOTH) {
            canvas.scale(-1, 1);
            dest.$x = -dest.$x - dest.$width;
        }
        if (flip === panda$gl$Flip.$VERTICAL || flip === panda$gl$Flip.$BOTH) {
            canvas.scale(1, -1);
            dest.$y = -dest.$y - dest.$height;
        }
        canvas.drawImage(img, dest.$x|0, dest.$y|0, dest.$width|0, 
                dest.$height|0);
        canvas.restore();
    },
    panda$gl$Renderer$copy_panda$gl$Texture_panda$gl$Rectangle_Real64_panda$gl$Point: function(renderer, texture, dest, rotation, rotationAxis) {
        var img = document.getElementById(texture.$native);
        var canvas = renderer.$native;
        canvas.save();
        var xAxis = ((rotationAxis.$x / img.width) * dest.$width)|0;
        var yAxis = ((rotationAxis.$y / img.height) * dest.$height)|0;
        canvas.translate(dest.$x + xAxis, dest.$y + yAxis);
        canvas.rotate(rotation);
        canvas.drawImage(img, -xAxis, -yAxis, dest.$width|0, dest.$height|0);
        canvas.restore();
    },
    panda$gl$Renderer$clear: function(renderer) {
        renderer.$native.fillRect(0, 0, 10000, 10000);
    },
    panda$gl$Renderer$present: function(renderer) {
    },
    panda$gl$GLMessageQueue$pumpEvents: function(glWindow) {
    },
    panda$gl$Window$startRenderLoop: function(glWindow, m) {
        var renderer = glWindow.$renderer
        setInterval(function() {
            renderer.$native.save();
            console.log("starting frame")
            m.$rawPtr()
            renderer.$native.restore();
        }, 1000 / 60);
    },
    panda$gl$GLMessageQueue$waitForEvent: function() {
    },
    panda$io$File$exists: function(file) {
        var path = getString(file.$path)
        return !path.endsWith("snail-jump.png") && !path.endsWith("snail-dead.png")
                && !path.endsWith("snake-jump.png") && !path.endsWith("snake-dead.png");
    },
    panda$threads$MessageQueue$initMessageQueue: function(mq) {
        mq.$nativeQueue = new Array()
    }
}

alert("remember that File.exists is still hacked")

function subclass(cl, name) {
    function f() {
        this.name = name;
        this.superclass = cl;
        if (typeof panda$core$Class === 'object')
            this.$cl = panda$core$Class;
    }
    f.prototype = cl;
    return new f();
}

function callInterfaceMethod(intf, index) {
    var cl = arguments[2].$cl;
    var method = cl.itable[intf][index];
    var finalArgs = new Array();
    for (var i = 2; i < arguments.length; i++)
        finalArgs.push(arguments[i]);
    return method.apply(null, finalArgs);
}

function panda$core$PandaCore$newArrayWithLength(cl, length) {
    var contents = new Array();
    for (var i = 0; i < length; i++) {
        if (cl === panda$collections$Array$panda$core$Int8 || 
                cl === panda$collections$Array$panda$core$Int16 ||
                cl === panda$collections$Array$panda$core$Int32 ||
                cl === panda$collections$Array$panda$core$Real32 ||
                cl === panda$collections$Array$panda$core$Real64 ||
                cl === panda$collections$Array$panda$core$Char)
            contents[i] = 0;
        else if (cl === panda$collections$Array$Int64)
            contents[i] = Int64.ZERO;
        else
            contents[i] = null;
    }
    return {
        contents: contents,
        $cl:      cl,
        $$length: length
    };
}

function panda$core$PandaCore$newArrayWithValues(cl) {
    var contents = new Array();
    var length = arguments.length - 1
    for (var i = 0; i < length; i++)
        contents[i] = arguments[i + 1];
    return {
        contents: contents,
        $cl:      cl,
        $$length: length
    };
}

function panda$core$PandaCore$newArrayWithRange(cl, src, offset, length) {
    var contents = new Array();
    for (var i = 0; i < length; i++)
        contents[i] = src.contents[i + offset];
    return {
        contents: contents,
        $cl:      cl,
        $$length: length
    };
}

function panda$core$PandaCore$newString(s) {
    var contents = new Array();
    for (var i = 0; i < s.length; i++)
        contents[i] = s.charCodeAt(i);
    var chars = {
        contents: contents,
        $cl:      panda$collections$Array$panda$core$Char,
        $$length: s.length
    };
    var result = {
        $chars: chars,
        $cl:    panda$core$String
    };
    return result;
}

function getString(s) {
    var result = "";
    var c = s.$chars.contents;
    for (var i = 0; i < c.length; i++)
        result += String.fromCharCode(c[i]);
    return result;
}

function toString(o) {
    return getString(o.$cl.vtable[5](o));
}

function panda$openTerm() {
    term = new Terminal({
      cols: 80,
      rows: 24,
      useStyle: true,
      screenKeys: true
    });
    term.open(document.body);
}