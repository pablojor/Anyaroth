
var functions = {
Fun: function (func, context) {
    return function () {
        this.reWrite(func.apply(context));
    }
},
Style: function (format) {
    let args = [];
    for (let element in arguments) {
        args.push(arguments[element]);
    }
    args = args.splice(1);
    return function () {
        let preStyle = this.styleLast.fontStyle;
        this.styleLast.fontStyle = format;
        this.reWrite(args);
        this.styleLast.fontStyle = preStyle;
    }
},
Color: function (color) {
    let args = [];
    for (let element in arguments) {
        args.push(arguments[element]);
    }
    args = args.splice(1);
    return function () {
        let preColor = this.styleLast.fill;
        this.styleLast.fill = color;
        this.reWrite(args);
        this.styleLast.fill = preColor;
    }
},
StrokeColor: function (color) {
    let args = [];
    for (let element in arguments) {
        args.push(arguments[element]);
    }
    args = args.splice(1);
    return function () {
        let preStrokeColor = this.styleLast.stroke;
        this.styleLast.stroke = color;
        this.reWrite(args);
        this.styleLast.stroke = preStrokeColor;
    }
},
FontWeight: function (style) {
    let args = [];
    for (let element in arguments) {
        args.push(arguments[element]);
    }
    args = args.splice(1);
    return function () {
        let preStyle = this.styleLast.fontWeight;
        this.styleLast.fontWeight = style;
        this.reWrite(args);
        this.styleLast.fontWeight = preStyle;
    }
},
Tremble: function (amplitud, frecuencia, longitudDeOnda) {
    let args = [];

    for (let element in arguments) {
        args.push(arguments[element]);
    }
    args = args.splice(3);
    return function () {
        let inicio = this.numberOfCharacters;
        this.reWrite(args);
        for (inicio; inicio < this.numberOfCharacters; inicio++) {
            this.getChildAt(inicio).initialY = this.getChildAt(inicio).y;
            this.getChildAt(inicio).update = function () {
                this.y = amplitud * Math.sin(this.game.time.totalElapsedSeconds() * 2 * Math.PI * frecuencia + this.parent.getChildIndex(this) / longitudDeOnda)
                    + this.initialY;
            };
        }
    }
},
VariableNumber: function (numberfunction, context, delay) {
    var value = numberfunction.apply(context);
    return function () {
        if (value !== numberfunction.apply(context)) {
            if (value > numberfunction.apply(context)) {
                value--;
            } else {
                value++;
            }
            this.game.time.create().add(delay, this.write, this).timer.start();
        }
        this.reWrite(value.toString());
    }
}
}
module.exports = functions;