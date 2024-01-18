import java.util.ArrayList;

public class CengTreeNodeInternal extends CengTreeNode
{
    private ArrayList<Integer> keys;
    private ArrayList<CengTreeNode> children;

    public CengTreeNodeInternal(CengTreeNode parent)
    {
        super(parent);

        // TODO: Extra initializations, if necessary.
        keys = new ArrayList<Integer>();
        children = new ArrayList<CengTreeNode>();
        this.type = CengNodeType.Internal;
    }

    // GUI Methods - Do not modify
    public ArrayList<CengTreeNode> getAllChildren()
    {
        return this.children;
    }
    public Integer keyCount()
    {
        return this.keys.size();
    }
    public Integer keyAtIndex(Integer index)
    {
        if(index >= this.keyCount() || index < 0)
        {
            return -1;
        }
        else
        {
            return this.keys.get(index);
        }
    }

    // Extra Functions

    public void insertChild(Integer index, CengTreeNode child)
    {
        this.children.add(index, child);
    }

    public void updateChild(Integer index, CengTreeNode child)
    {
        this.children.set(index, child);
    }

    public CengTreeNode get_childrenAt(Integer index)
    {

        return this.children.get(index);
    }
    public Integer findIndex(Integer key)
    {
        Integer index = 0;
        while(index < this.keys.size() && key >= this.keys.get(index))
            index += 1;

        return index;
    }

    public Integer indexofChild(CengTreeNode src)
    {
        return this.children.indexOf(src);
    }

    public CengTreeNode find_Path(Integer key)
    {
        return this.children.get(findIndex(key));
    }

    public CengTreeNode getChild(Integer index)
    {
        return this.children.get(index);
    }

    public void insertKey(Integer index, Integer key)
    {
        this.keys.add(index, key);
    }

    ArrayList<Integer> getKeys()
    {
        return this.keys;
    }


    public CengTreeNodeInternal push_up(CengTreeNodeInternal src) {
        int midIndex = src.keyCount() / 2;
        int midKey = src.keyAtIndex(midIndex);

        CengTreeNodeInternal parentNode = (CengTreeNodeInternal) src.getParent();
        CengTreeNodeInternal leftNode = new CengTreeNodeInternal(parentNode);
        CengTreeNodeInternal rightNode = new CengTreeNodeInternal(parentNode);

        for (int i = 0; i < midIndex; i++)
        {
            CengTreeNode child = src.getChild(i);
            child.setParent(leftNode);
            leftNode.insertChild(i, child);

            int childKey = src.keyAtIndex(i);
            leftNode.insertKey(i, childKey);
        }

        for (int i = midIndex + 1; i < src.keyCount(); i++)
        {
            CengTreeNode child = src.getChild(i);
            child.setParent(rightNode);
            rightNode.insertChild(i - midIndex - 1, child);

            int childKey = src.keyAtIndex(i);
            rightNode.insertKey(i - midIndex - 1, childKey);
        }


        CengTreeNode midChild = src.getChild(midIndex);
        midChild.setParent(leftNode);
        leftNode.insertChild(midIndex, midChild);

        CengTreeNode lastChild = src.getChild(src.keyCount());
        lastChild.setParent(rightNode);
        rightNode.insertChild(src.keyCount() - midIndex - 1, lastChild);

        if (parentNode == null)
        {
            parentNode = new CengTreeNodeInternal(null);
            leftNode.setParent(parentNode);
            rightNode.setParent(parentNode);

            parentNode.insertKey(0, midKey);
            //parentNode.keys.add(0, midKey);
            parentNode.insertChild(0, leftNode);
            parentNode.insertChild(1, rightNode);
        }
        else
        {
            int keyIndex = parentNode.indexofChild(src);
            parentNode.insertKey(keyIndex, midKey);
            parentNode.updateChild(keyIndex, leftNode);
            parentNode.insertChild(keyIndex + 1, rightNode);
        }

        return parentNode;
    }

}
