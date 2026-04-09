public class File extends Component{

    public File(String name, int size, String directory){
        this.name = name;
        this.size = size;
        this.type = "File";
        this.directory = directory;
        this.componentCount = 1;
        this.creationTime = "13 December, 2023 5:12 PM";
    }

    @Override
    public void details() {
        System.out.println("Name: " + name);
        System.out.println("Type: " + type);
        System.out.println("Size: " + size + "kB");
        System.out.println("Directory: " + directory);
        System.out.println("Component Count: " + componentCount);
        System.out.println("Creation Time: " + creationTime);
    }

    @Override
    public int calculateSize() {
        return this.size;
    }

    @Override
    public void listing() {
        System.out.println(name + "\t" + size + " kB\t" + creationTime);
    }

    @Override
    public void delete(String name) {
        return;
    }

    @Override
    public void recursiveDelete(String name) {
        return;
    }

}
