app.component('dynamic-window', {
    data() {
        return {
            collapsed: false,
            visible: true,
            left: 500,
            top: 100,
            isMovingWindow: false,
            actionMenuActive: false
        }
    },
    props: {
        title: {
            type: String,
            required: true
        }
    },
    template:
    /*html*/
    `
    <transition name='close' >

    <div 
        v-if="visible"
        @mousemove="mouseMoveHandler"
        @mouseup="mouseUpHandler"
        :class="{ 'dynamic-window-selected' : isMovingWindow }"
        ref="dw"
        class="dynamic-window" 
        :style="{ 'margin-left': left + 'px', 'margin-top' : top + 'px' }"
        >

        <div class="nav-window">
        <div class="nav-window noselect" @mousedown="startMovement">
            <div><h5 style="margin: 10px"><p v-html="title"><b>{{ title }}</b></p></h5></div>

            <div class="window-actions" @mousedown="actionMenuSelected" style="'margin-left': auto">
                <button v-if="!collapsed" type="button" v-on:click="collapse" class="nav-button btn btn-dark"><i class="fa fa-arrow-up"></i></button>
                <button v-else type="button" v-on:click="expand" class="nav-button btn btn-dark"><i class="fa fa-arrow-down"></i></button>
                <button type="button" v-on:click="minimize" class="window-action-btn nav-button btn btn-dark"><i class="fa fa-window-minimize"></i></button>
                <button type="button" v-on:click="close" class="window-action-btn nav-button btn btn-dark"><i class="fa fa-times"></i></button>
            </div>
        </div>
        </div>


        <transition name='collapse' >
            <div class="window-content" v-if="!collapsed">
                <slot></slot>
            </div>
        </transition>


    </div>
    </transition>

    `,
    methods: {
        setVisible() {
            this.visible = true
        },
        minimize() {
            let info = {
                setVisible: this.setVisible,
                title: this.title
            }
            this.visible = false
            this.$emit('minimize', info)
        },
        actionMenuSelected() {
            this.actionMenuActive = true
        },
        startMovement() {
            if(!this.actionMenuActive) {
                this.isMovingWindow = true
            }
        },
        mouseMoveHandler(event) {
            if (this.isMovingWindow) {
                if (event.clientX < window.innerWidth - 115 && event.clientX > 100 && event.clientY > 89) {
                    this.left = event.clientX - this.$refs.dw.clientWidth/2;
                    this.top = event.clientY - 30;
                }
            }
        },
        expand() {
            this.collapsed = false
        },
        collapse() {
            this.collapsed = true
        },
        close() {
            if (confirm("Tem certeza de que deseja fechar esta janela?")) {
                this.visible = false
            } else {
            } 
        },
        mouseUpHandler() {
            this.isMovingWindow = false;  
            this.actionMenuActive = false
        }
    }
})