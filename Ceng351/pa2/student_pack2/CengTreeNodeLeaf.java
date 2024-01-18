import java.util.ArrayList;

public class CengTreeNodeLeaf extends CengTreeNode
{
    private ArrayList<CengBook> books;
    // TODO: Any extra attributes

    public CengTreeNodeLeaf(CengTreeNode parent)
    {
        super(parent);

        // TODO: Extra initializations
        books = new ArrayList<CengBook>();
        this.type = CengNodeType.Leaf;

    }

    // GUI Methods - Do not modify
    public int bookCount()
    {
        return books.size();
    }
    public Integer bookKeyAtIndex(Integer index)
    {
        if(index >= this.bookCount()) {
            return -1;
        } else {
            CengBook book = this.books.get(index);

            return book.getBookID();

        }
    }

    // Extra Functions

    public void addBook(CengBook book){
        Integer index = 0;
        Integer bookID = book.getBookID();

        while(index < this.books.size() && bookID > this.books.get(index).getBookID())
        {
            index += 1;
        }
        this.books.add(index, book);
    }

    public void insertBook(Integer index, CengBook book)
    {
        this.books.add(index, book) ;
    }

    public CengBook bookAtIndex(Integer index)
    {
        if(index >= this.bookCount())
        {
            return null;
        }
        else
        {
            return this.books.get(index);

            //return book.getBookID();
        }
    }

    public ArrayList<CengBook> getbooks()
    {
        return books;
    }

    public CengTreeNodeInternal split_leaf(CengTreeNodeLeaf src){

        Integer mid_index =  src.bookCount()/2;
        Integer mid_key = src.bookKeyAtIndex(mid_index);
        CengTreeNodeInternal parent_dummy = (CengTreeNodeInternal) src.getParent();

        CengTreeNodeLeaf left_node = new CengTreeNodeLeaf(parent_dummy);
        CengTreeNodeLeaf right_node = new CengTreeNodeLeaf(parent_dummy);

        for(int i = 0; i < mid_index; i++)
        {
            left_node.insertBook(i, src.bookAtIndex(i));
        }

        for(int i = mid_index; i < src.bookCount(); i++)
        {
            right_node.insertBook(i - mid_index, src.bookAtIndex(i));
        }

        if(parent_dummy == null)
        {
            parent_dummy = new CengTreeNodeInternal(null);
            left_node.setParent(parent_dummy);
            right_node.setParent(parent_dummy);

            parent_dummy.insertKey(0, mid_key);
            parent_dummy.insertChild(0, left_node);
            parent_dummy.insertChild(1, right_node);
        }
        else
        {
            Integer key_index = parent_dummy.indexofChild(src);
            parent_dummy.insertKey(key_index, mid_key);
            parent_dummy.updateChild(key_index, left_node);
            parent_dummy.insertChild(key_index + 1, right_node);
        }

        return parent_dummy;
    }
}
