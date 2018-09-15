// Copyright (c) bis83. Distributed under the MIT License.

class Scene {
    constructor() {
        this.reset();
    }

    onload(input, fx) {
        fx.sprite.load("img/title.png");
    }

    reset() {
    }

    update(input) {
    }

    draw(fx) {
        fx.sprite.texture("img/title.png");
        fx.sprite.uv(0, 0, 1, 1);
        fx.sprite.color(1, 1, 1, 1);
        fx.sprite.trans(480, 270, 640, 320, 0);
        fx.sprite.draw();
    }
}