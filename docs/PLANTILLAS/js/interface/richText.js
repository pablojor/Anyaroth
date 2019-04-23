'use strict';


var RichText = function (game, x, y, lineWidth, text, style, parent) {
    Phaser.Group.call(this, game, parent);
    this._protoText = text;
    this.numberOfCharacters = 0;
    this.x = x;
    this.y = y;
    this.xLast = 0;
    this.yLast = 0;
    this.indexFirstParragraphLetter = 0;
    this.align = style.align === undefined ? 'left' : style.align;
    this.styleLast = {
        font: style.font === undefined ? 'Minecraft' : style.font,
        fontStyle: style.fontStyle === undefined ? 'normal' : style.fontStyle,
        fontVariant: style.fontVariant === undefined ? 'normal' : style.fontVariant,
        fontWeight: style.fontWeight === undefined ? 'normal' : style.fontWeight,
        fontSize: style.fontSize === undefined ? 10 : style.fontSize,
        backgroundColor: style.backgroundColor === undefined ? null : style.backgroundColor,
        fill: style.fill === undefined ? '#000000' : style.fill,
        align: 'left',
        boundsAlignH: style.boundsAlignH === undefined ? 'left' : style.boundsAlignH,
        boundsAlignV: style.boundsAlignV === undefined ? 'top' : style.boundsAlignV,
        stroke: style.stroke === undefined ? 'black' : style.stroke,
        strokeThickness: style.strokeThickness === undefined ? 0 : style.strokeThickness,
        wordWrap: style.wordWrap === undefined ? false : style.wordWrap,
        wordWrapWidth: style.wordWrapWidth === undefined ? false : style.wordWrapWidth,
        maxLines: style.maxLines === undefined ? 0 : style.maxLines
    };
    this.lineWidth = lineWidth;
    this.lineHeight = this.styleLast.fontSize;
    this.write();
}

RichText.prototype = Object.create(Phaser.Group.prototype);
RichText.prototype.constructor = RichText;

RichText.prototype.write = function () {
    this.indexFirstParragraphLetter = 0;
    this.removeAll(true);
    this.xLast = 0;
    this.yLast = 0;
    this.numberOfCharacters = 0;
    this.reWrite(this._protoText);
    if (this.children.length !== 0) {
        if (this.align === 'center') {
            let tmpwidth = 0;
            for (let j = this.indexFirstParragraphLetter; j < this.children.length; j++) {
                tmpwidth += this.getChildAt(j).width;
            }
            tmpwidth = (this.lineWidth - tmpwidth) / 2;
            if (this.getChildAt(this.children.length - 1).text === ' ') { tmpwidth += this.getChildAt(this.children.length - 1).width / 2 }
            for (let j = this.indexFirstParragraphLetter; j < this.children.length; j++) {
                this.getChildAt(j).x += tmpwidth;
            }
            this.indexFirstParragraphLetter = this.children.length + 1;
        } else if (this.align === 'right') {
            let tmpwidth = 0;
            for (let j = this.indexFirstParragraphLetter; j < this.children.length; j++) {
                tmpwidth += this.getChildAt(j).width;
            }
            tmpwidth = (this.lineWidth - tmpwidth);
            if (this.getChildAt(this.children.length - 1).text === ' ') { tmpwidth += this.getChildAt(this.children.length - 1).width }
            for (let j = this.indexFirstParragraphLetter; j < this.children.length; j++) {
                this.getChildAt(j).x += tmpwidth;
            }
            this.indexFirstParragraphLetter = this.children.length + 1;
        }
    }
}

RichText.prototype.reWrite = function (proto) {
    if (typeof (proto) === 'string') {
        let presize = this.children.length;
        for (let i = 0; i < proto.length; i++) {
            let a = this.add(new Phaser.Text(this.game, this.xLast, this.yLast, proto.charAt(i), this.styleLast));
            if (proto.charAt(i) === '\n') {
                this.xLast = 0;
                this.yLast += this.lineHeight;
                this.indexFirstParragraphLetter = presize + i + 1;
            } else if (!(proto.charAt(i) === ' ' && this.xLast === 0)) {
                this.xLast += a.width;
                if (this.xLast > this.lineWidth) {
                    if (a.text !== ' ') {
                        let index = Math.min(presize + i-1, this.children.length - 1);
                        let temporalWidth = 0;
                        while (index >= 0 && this.getChildAt(index).text !== ' ') {
                            temporalWidth += this.getChildAt(index).width;
                            index--;
                        }
                        if (index < 0) {
                            index = 0;
                        }
                        if (this.getChildAt(index).text === ' ') {
                            index = Math.min(index + 1, this.children.length - 1);
                        }
                        if (temporalWidth > this.lineWidth) {
                            this.xLast = this.getChildAt(index).x;
                            this.yLast = this.getChildAt(index).y;
                        } else {
                            this.xLast = 0;
                            this.yLast += this.lineHeight;
                        }
                        for (let j = index; j <= presize + i; j++) {
                            if (this.xLast > this.lineWidth) {
                                this.xLast = 0;
                                this.yLast += this.lineHeight;
                            }

                            this.getChildAt(j).x = this.xLast;
                            this.getChildAt(j).y = this.yLast;
                            this.xLast += this.getChildAt(j).width;
                        }
                        if (this.xLast > this.lineWidth) {
                            this.xLast = 0;
                            this.yLast += this.lineHeight;
                        }
                        if (this.align === 'center') {
                            let tmpwidth = 0;
                            for (let j = this.indexFirstParragraphLetter; j < index; j++) {
                                tmpwidth += this.getChildAt(j).width;
                            }
                            tmpwidth = (this.lineWidth - tmpwidth) / 2;
                            if (this.getChildAt(index - 1).text === ' ') { tmpwidth += this.getChildAt(index - 1).width / 2 }
                            for (let j = this.indexFirstParragraphLetter; j < index; j++) {
                                this.getChildAt(j).x += tmpwidth;
                            }

                        } else if (this.align === 'right') {
                            let tmpwidth = 0;
                            for (let j = this.indexFirstParragraphLetter; j < index; j++) {
                                tmpwidth += this.getChildAt(j).width;
                            }
                            tmpwidth = (this.lineWidth - tmpwidth);
                            if (index - 1 >= 0 && this.getChildAt(index - 1).text === ' ') { tmpwidth += this.getChildAt(index - 1).width }
                            for (let j = this.indexFirstParragraphLetter; j < index; j++) {
                                this.getChildAt(j).x += tmpwidth;
                            }
                        }
                        this.indexFirstParragraphLetter = index;
                    } else {
                        if (this.align === 'center') {
                            let tmpwidth = 0;
                            for (let j = this.indexFirstParragraphLetter; j < i; j++) {
                                tmpwidth += this.getChildAt(j).width;
                            }
                            if (this.getChildAt(i - 1).text === ' ') { tmpwidth += this.getChildAt(i - 1).width / 2 }
                            tmpwidth = (this.lineWidth - tmpwidth) / 2;
                            for (let j = this.indexFirstParragraphLetter; j < presize + i; j++) {
                                this.getChildAt(j).x += tmpwidth;
                            }

                        } else if (this.align === 'right') {
                            let tmpwidth = 0;
                            for (let j = this.indexFirstParragraphLetter; j < presize + i; j++) {
                                tmpwidth += this.getChildAt(j).width;
                            }
                            tmpwidth = (this.lineWidth - tmpwidth);
                            if (i - 1 >= 0 && this.getChildAt(presize + i - 1).text === ' ') { tmpwidth += this.getChildAt(presize + i - 1).width }
                            for (let j = this.indexFirstParragraphLetter; j < presize + i; j++) {
                                this.getChildAt(j).x += tmpwidth;
                            }

                        }
                        this.indexFirstParragraphLetter = presize + i + 1;
                        this.xLast = 0;
                        this.yLast += this.lineHeight;
                    }
                }
            }
            this.numberOfCharacters++;
        }
    } else if (typeof (proto) === 'function') {
        proto.apply(this);
    } else if (Array.isArray(proto)) {
        for (let element in proto) {
            this.reWrite(proto[element]);
        }
    }
}

Object.defineProperty(RichText.prototype, 'text',{
    set: function(text) {
        this._protoText = text;
        this.write();
        
    }
});

module.exports = RichText;