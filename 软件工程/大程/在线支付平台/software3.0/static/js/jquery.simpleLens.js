/*!
 * jQuery Lens Simple Plugin
 * Copyright (c) 2014 Pietro Simone Di Chiara
 * Version: 1.0.1 (05-APR-2013)
 * Licensed under the MIT license:
 * http://www.opensource.org/licenses/mit-license.php
 * Requires: jQuery v1.7.0 or later
 */
(function ($) {
    "use strict";

    var ver = 'simpleLens-1.0.1';

    function debug(message) {
        if (window.console) {
            console.log(message);
        }
    }

    $.fn.simpleLens = function (options) {
        var opts = $.extend({}, $.fn.simpleLens.defaults, options);

        var big_image = {
            init: function (image) {
                this.height = image.height();
                this.width = image.width();
                this.offset = image.offset();
                this.position = image.position();

                this.calc_image_limits();
            },
            calc_image_limits: function(){
                this.limits = {
                    x_left : (this.position.left),
                    x_right : (this.position.left + this.width),
                    y_top : (this.position.top),
                    y_bottom : (this.position.top + this.height)
                }
            },
            calc_view_position: function (e) {
                return {
                    org_x: (e.pageX - this.offset.left),
                    org_y: (e.pageY - this.offset.top)
                }
            }
        };

        var cursor = {
            init: function(parent_anchor, lens_container, ratio, position){
                this.parent_anchor = parent_anchor;
                this.lens_container = lens_container;
                this.ratio = ratio;

                this.cursor_position = {
                    'top': 0,
                    'left': 0
                };

                this.calc_cursor_size();
                this.insert_cursor(position.org_x, position.org_y);
            },
            destroy: function(){
                $('.' + opts.cursor_class).remove();
            },
            calc_cursor_size: function () {
                this.cursor_height = this.lens_container.height() / this.ratio.x;
                this.cursor_width = this.lens_container.width() / this.ratio.y;
                this.height_center = (this.cursor_height / 2);
                this.width_center = (this.cursor_width / 2);
            },
            update_cursor_position: function (x, y) {
                var new_y = (y - this.height_center);
                var new_bottom_y = (y + this.height_center);
                var new_x = (x - this.width_center);
                var new_right_x = (x + this.width_center);

                var limits = big_image.limits;
                if (parseFloat(limits.y_top) > parseFloat(new_y)) {
                    new_y = limits.y_top;
                } else if (parseFloat(new_bottom_y) > parseFloat(limits.y_bottom)) {
                    new_y = limits.y_bottom - this.cursor_height;
                }

                if (parseFloat(limits.x_left) > parseFloat(new_x)) {
                    new_x = limits.x_left;
                } else if (parseFloat(new_right_x) > parseFloat(limits.x_right)) {
                    new_x = limits.x_right - this.cursor_width;
                }

                this.cursor_position = {
                    'top': new_y,
                    'left': new_x,
                    'center_top': new_y + this.height_center,
                    'center_left': new_x + this.width_center
                };

                if (this.cursor !== undefined) {
                    this.cursor.css(this.cursor_position);
                }
            },
            insert_cursor: function (x, y) {
                this.cursor = $('<div>', {'class': opts.cursor_class});
                this.cursor.css({
                    'height': this.cursor_height + 'px',
                    'width': this.cursor_width + 'px'
                });

                this.cursor.appendTo(this.parent_anchor);
                return this.update_cursor_position(x, y);
            }
        };

        var lens = {
            init: function(parent_anchor){
                this.parent_anchor = parent_anchor;
                this.parent_div = parent_anchor.parent(opts.parent_class);
                this.lens_image_url = parent_anchor.attr(opts.lens_image_attr);
                this.lens_container = $('<div>', {'class': opts.lens_class});
                this.lens_image = $('<img>');
                big_image.init(parent_anchor.find(opts.big_image_class));

                if (this.lens_image_url === undefined) {
                    debug('Cannot find lens image. URL: ' + this.lens_image_url);
                    debug(that);
                    debug(parent_anchor);
                    debug(lens_image_url);
                }
            },
            update_lens_position: function (position) {
                this.lens_image.css({
                    'top': position.top,
                    'left': position.left
                });
            },
            calc_lens_position: function(cursor_position){
                return {
                    left: (cursor_position.center_left * this.ratio.x - this.container.width) * -1,
                    top: (cursor_position.center_top * this.ratio.y - this.container.height) * -1
                }
            },
            lens_event_bind: function () {
                var that = this;
                var mouse_callback = function (mouse) {
                    var position = big_image.calc_view_position(mouse);
                    cursor.update_cursor_position(position.org_x, position.org_y);
                    that.update_lens_position(that.calc_lens_position(cursor.cursor_position, that.ratio, that.container));
                };

                this.parent_anchor.mousemove(mouse_callback);
            },
            lens_event_unbind: function(){
                if(this.parent_anchor !== undefined){
                    this.parent_anchor.unbind('mousemove');
                }
            },
            destroy: function(){
                cursor.destroy();

                if(this.lens_container !== undefined && this.lens_container.length > 0){
                    $('.' + opts.lens_class).remove();
                    this.lens_event_unbind();
                }
            },
            load: function(e){
                var that = this;

                this.lens_container.appendTo(this.parent_div);

                var margin_top = (this.lens_container.height() / 2) - 25,
                    loading_image = $('<img>', {'src': opts.loading_image})
                        .css("margin-top", margin_top);
                this.lens_container.html(loading_image);

                this.lens_image.load(function () {
                    that.lens_container.html(that.lens_image);

                    that.container = {
                        width: that.lens_container.width() / 2,
                        height: that.lens_container.height() / 2
                    };

                    that.img_size = {
                        width: that.lens_image.width(),
                        height: that.lens_image.height()
                    };

                    that.ratio = {
                        y: that.lens_image.height() / big_image.height,
                        x: that.lens_image.width() / big_image.width
                    };

                    var position = big_image.calc_view_position(e);
                    cursor.init(that.parent_anchor, that.lens_container, that.ratio, position);
                    that.update_lens_position(that.calc_lens_position(cursor.cursor_position));

                    that.lens_event_bind();
                }).attr('src', this.lens_image_url);
            }
        };

        var init = function (e) {
            var parent_anchor =  $(this);

            lens.init(parent_anchor);
            lens.load(e);
        };

        var destroy = function () {
            lens.destroy();
        };

        $(this).parents(opts.parent_class).on(opts.open_lens_event, opts.anchor_parent_class, init);
        $(this).parents(opts.parent_class).on('mouseleave', opts.anchor_parent_class, destroy);

    };

    $.fn.simpleLens.ver = function () { return ver; };

    $.fn.simpleLens.defaults = {
        anchor_parent_class: '.simpleLens-lens-image',
        lens_image_attr: 'data-lens-image',
        big_image_class: '.simpleLens-big-image',
        parent_class: '.simpleLens-big-image-container',
        lens_class: 'simpleLens-lens-element',
        cursor_class: 'simpleLens-mouse-cursor',
        loading_image: '../img/view-slider/loading.gif',
        open_lens_event: 'mouseenter'
    };

})( jQuery );