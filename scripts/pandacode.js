function applyToTree(node, f) {
    f(node)
    node = node.firstChild
    while (node) {
        applyToTree(node, f)
        node = node.nextSibling
    }
}

var highlightedNode

var oldLoad = window.onload
window.onload = function() {
    if (oldLoad)
        oldLoad()

    applyToTree(document.body, function (node) {
        if (node.className === "block") {
            node.onmouseover = function(e) {
                if (highlightedNode)
                    highlightedNode.className = "block"
                node.className = "block mouseover"
                highlightedNode = node
                e.stopPropagation()
                return false
            }
            node.onmouseout = function() {
                if (highlightedNode == node) {
                    node.className = "block"
                    highlightedNode = null
                }
            }
        }
    })
}
