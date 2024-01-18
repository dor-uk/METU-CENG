import java.util.ArrayList;

public class CengTree
{
    public CengTreeNode root;
    // Any extra attributes...

    public CengTree(Integer order)
    {
        CengTreeNode.order = order;
        // TODO: Initialize the class
        root = new CengTreeNodeLeaf(null);

    }

    public void addBook(CengBook book)
    {
        // TODO: Insert Book to Tree
        CengTreeNodeLeaf target = ((CengTreeNodeLeaf) findLeaf(book));
        CengTreeNodeInternal parent_node;
        target.addBook(book);

        if(target.bookCount() > 2*CengTreeNode.order)
        {
            parent_node = target.split_leaf(target);

            while(parent_node.keyCount() > 2*CengTreeNode.order)
            {
                parent_node = parent_node.push_up(parent_node);
            }
            if(parent_node.getParent() == null)
            {
                root = parent_node;
            }
        }
    }

    private CengTreeNode findLeaf(CengBook book){
        CengTreeNode tmp = root;

        while(tmp.getType() != CengNodeType.Leaf)
        {
            tmp = ((CengTreeNodeInternal) tmp).find_Path(book.getBookID());
        }

        return tmp;
    }

    public ArrayList<CengTreeNode> searchBook(Integer bookID)
    {
        // TODO: Search within whole Tree, return visited nodes.
        // Return null if not found.

        CengTreeNode searcher = root;
        int indentation = 0;
        while(searcher.type != CengNodeType.Leaf)
        {

            ArrayList<Integer> keys = ((CengTreeNodeInternal) searcher).getKeys();
            int idx = keys.size();

            for(int idx_finder = 0; idx_finder < keys.size(); idx_finder++)
            {
                if( keys.get(idx_finder) > bookID)
                {
                    idx = idx_finder;
                    break;
                }
            }

            tab_adder(indentation);
            System.out.println("<index>");
            for(int k: keys)
            {
                tab_adder(indentation);
                System.out.println(k);
            }

            tab_adder(indentation);
            System.out.println("</index>");
            CengTreeNode child = ((CengTreeNodeInternal) searcher).get_childrenAt(idx);
            searcher = child;
            indentation++;

        }
        ArrayList<CengBook> books =((CengTreeNodeLeaf) searcher).getbooks();
        CengBook dummy = null;
        for(CengBook book: books){
            if(book.getBookID() == bookID)
            {
                dummy = book;
                break;
            }
        }

        if(dummy == null)
        {
            System.out.println("Could not find " + bookID + ".");
        }
        else{

            tab_adder(indentation);

            System.out.println("<record>" + dummy.fullName() + "</record>");

        }

        return null;
    }

    public void printTree()
    {
        // TODO: Print the whole tree to console
        recursive_print(root, root.level - 1);
    }

    private void recursive_print(CengTreeNode root, int level){

        if(root.getType() == CengNodeType.Leaf)
        {
            tab_adder(level);
            System.out.println("<data>");

            for(int k = 0 ; k < ((CengTreeNodeLeaf)root).bookCount(); k++)
            {
                CengBook book = ((CengTreeNodeLeaf)root).bookAtIndex(k);
                for (int i = 0; i < level; i++) {
                    System.out.print("\t");
                }

                System.out.println("<record>" + book.fullName() + "</record>");
            }

            tab_adder(level);
            System.out.println("</data>");
        }
        else
        {

            tab_adder(level);
            System.out.println("<index>");
            for(int k = 0; k < ((CengTreeNodeInternal)root).keyCount(); k++)
            {

                tab_adder(level);
                System.out.println(((CengTreeNodeInternal)root).keyAtIndex(k));
            }


            tab_adder(level);
            System.out.println("</index>");
            for(int i = 0; i < ((CengTreeNodeInternal)root).keyCount() + 1; i++)
            {
                CengTreeNode next_children = ((CengTreeNodeInternal)root).get_childrenAt(i);
                recursive_print(next_children, next_children.level - 1);
            }

        }
    }

    private void tab_adder(int level){
        for (int i = 0; i < level; i++) {
            System.out.print("\t");
        }
    }

    // Any extra functions...
}
