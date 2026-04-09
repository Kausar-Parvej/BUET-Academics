public abstract class Component {
    protected String name;
    protected int size;
    protected String type;
    protected String directory;
    protected int componentCount;
    protected String creationTime;

    public String getName() {
        return name;
    }

    public int getSize() {
        return size;
    }

    public String getType() {
        return type;
    }

    public String getDirectory() {
        return directory;
    }

    public int getComponentCount() {
        return componentCount;
    }

    public String getCreationTime() {
        return creationTime;
    }



    public abstract void details();
    public abstract int calculateSize();

    public abstract void listing();
    public abstract void delete(String name);
    public abstract void recursiveDelete(String name);


}
