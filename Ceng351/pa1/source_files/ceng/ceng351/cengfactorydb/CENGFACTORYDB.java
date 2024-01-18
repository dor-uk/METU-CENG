package ceng.ceng351.cengfactorydb;

import java.sql.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class CENGFACTORYDB implements ICENGFACTORYDB{
    private static String user = "e2522225"; // TODO: Your userName
    private static String password = "(XUz8G~x+KjH"; //  TODO: Your password
    private static String host = "144.122.71.128"; // host name
    private static String database = "db2522225"; // TODO: Your database name
    private static int port = 8080; // port

    private static Connection connection = null;

    /**
     * Place your initialization code inside if required.
     *
     * <p>
     * This function will be called before all other operations. If your implementation
     * need initialization , necessary operations should be done inside this function. For
     * example, you can set your connection to the database server inside this function.
     */
    public void initialize() {

        String url = "jdbc:mysql://" + this.host + ":" + this.port + "/" + this.database + "?useSSL=false";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            this.connection =  DriverManager.getConnection(url, this.user, this.password);
        } catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }

    }

    /**
     * Should create the necessary tables when called.
     *
     * @return the number of tables that are created successfully.
     */

    public int createTables() {
        int tables_created = 0;

        String query_create_Factory = "CREATE TABLE IF NOT EXISTS Factory(" +
                "factoryId INT NOT NULL, " +
                "factoryName TEXT, " +
                "factoryType TEXT, " +
                "country TEXT, " +
                "PRIMARY KEY (factoryId));";

        String query_create_Employee = "CREATE TABLE IF NOT EXISTS Employee(" +
                "employeeId INT NOT NULL, " +
                "employeeName TEXT, " +
                "department TEXT, " +
                "salary INT, " +
                "PRIMARY KEY (employeeId));";

        String query_create_Works_In = "CREATE TABLE IF NOT EXISTS Works_In(" +
                "factoryId INT NOT NULL, " +
                "employeeId INT NOT NULL, " +
                "startDate DATE, " +
                "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId), " +
                "FOREIGN KEY (employeeId) REFERENCES Employee(employeeId) " +
                "ON DELETE CASCADE, " +
                "PRIMARY KEY (factoryId, employeeId));";

        String query_create_Product = "CREATE TABLE IF NOT EXISTS Product(" +
                "productId INT NOT NULL, " +
                "productName TEXT, " +
                "productType TEXT, " +
                "PRIMARY KEY (productId));";

        String query_create_Produce = "CREATE TABLE IF NOT EXISTS Produce(" +
                "factoryId INT NOT NULL, " +
                "productId INT NOT NULL, " +
                "amount INT, " +
                "productionCost INT, " +
                "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId), " +
                "FOREIGN KEY (productId) REFERENCES Product(productId), " +
                "PRIMARY KEY (factoryId, productId));";

        String query_create_Shipment = "CREATE TABLE IF NOT EXISTS Shipment(" +
                "factoryId INT NOT NULL, " +
                "productId INT NOT NULL, " +
                "amount INT, " +
                "pricePerUnit INT, " +
                "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId), " +
                "FOREIGN KEY (productId) REFERENCES Product(productId), " +
                "PRIMARY KEY (factoryId, productId));";

        //Factory
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_create_Factory);
            tables_created++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Employee
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_create_Employee);
            tables_created++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Works_In
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_create_Works_In);
            tables_created++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Product
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_create_Product);
            tables_created++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Produce
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_create_Produce);
            tables_created++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Shipment
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_create_Shipment);
            tables_created++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }


        return tables_created;
    }

    /**
     * Should drop the tables if exists when called.
     *
     * @return the number of tables are dropped successfully.
     */

    public int dropTables() {
        int dropped_tables = 0;

        String query_drop_Factory = "DROP TABLE IF EXISTS Factory;";
        String query_drop_Employee = "DROP TABLE IF EXISTS Employee;";
        String query_drop_Works_In = "DROP TABLE IF EXISTS Works_In;";
        String query_drop_Product = "DROP TABLE IF EXISTS Product;";
        String query_drop_Produce = "DROP TABLE IF EXISTS Produce;";
        String query_drop_Shipment = "DROP TABLE IF EXISTS Shipment;";


        //Shipment
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_drop_Shipment);
            dropped_tables++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Produce
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_drop_Produce);
            dropped_tables++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Product
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_drop_Product);
            dropped_tables++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Works_In
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_drop_Works_In);
            dropped_tables++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }


        //Employee
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_drop_Employee);
            dropped_tables++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        //Factory
        try{
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(query_drop_Factory);
            dropped_tables++;
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        return dropped_tables;
    }

    /**
     * Should insert an array of Factory into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertFactory(Factory[] factories) {

        int number_of_factory = 0;
        String insert_query = "INSERT INTO Factory(" +
                "factoryId, " +
                "factoryName, " +
                "factoryType, " +
                "country) VALUES (?, ?, ?, ?);";

        for(int i = 0; i < factories.length; i++){

            Factory target = factories[i];

            try{
                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                prep_statement.setInt(1, target.getFactoryId());
                prep_statement.setString(2, target.getFactoryName());
                prep_statement.setString(3, target.getFactoryType());
                prep_statement.setString(4, target.getCountry());
                prep_statement.executeUpdate();
                number_of_factory++;
                prep_statement.close();
            }catch (SQLException e) {
                e.printStackTrace();
            }

        }

        return number_of_factory;
    }

    /**
     * Should insert an array of Employee into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertEmployee(Employee[] employees) {
        int number_of_employee = 0;
        String insert_query = "INSERT INTO Employee(" +
                "employeeId, " +
                "employeeName, " +
                "department, " +
                "salary) VALUES (?, ?, ?, ?);";

        for(int i = 0; i < employees.length; i++){

            Employee target = employees[i];

            try{
                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                prep_statement.setInt(1, target.getEmployeeId());
                prep_statement.setString(2, target.getEmployeeName());
                prep_statement.setString(3, target.getDepartment());
                prep_statement.setInt(4, target.getSalary());
                prep_statement.executeUpdate();
                number_of_employee++;
                prep_statement.close();
            }catch (SQLException e) {
                e.printStackTrace();
            }

        }

        return number_of_employee;
    }

    /**
     * Should insert an array of WorksIn into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertWorksIn(WorksIn[] worksIns) {

        int number_of_works = 0;
        String insert_query = "INSERT INTO Works_In(" +
                "factoryId, " +
                "employeeId, " +
                "startDate) VALUES (?, ?, ?);";

        for (int i = 0; i < worksIns.length; i++) {

            WorksIn target = worksIns[i];

            try {
                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                prep_statement.setInt(1, target.getFactoryId());
                prep_statement.setInt(2, target.getEmployeeId());
                prep_statement.setString(3, target.getStartDate());

                prep_statement.executeUpdate();
                number_of_works++;
                prep_statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }

        }

        return number_of_works;
    }
    /**
     * Should insert an array of Product into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduct(Product[] products) {
        int number_of_products = 0;
        String insert_query = "INSERT INTO Product(" +
                "productId, " +
                "productName, " +
                "productType) VALUES (?, ?, ?);";

        for(int i = 0; i < products.length; i++){

            Product target = products[i];

            try{
                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                prep_statement.setInt(1, target.getProductId());
                prep_statement.setString(2, target.getProductName());
                prep_statement.setString(3, target.getProductType());
                prep_statement.executeUpdate();
                number_of_products++;
                prep_statement.close();
            }catch (SQLException e) {
                e.printStackTrace();
            }

        }

        return number_of_products;
    }


    /**
     * Should insert an array of Produce into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduce(Produce[] produces) {
        int number_of_produce = 0;
        String insert_query = "INSERT INTO Produce(" +
                "factoryId, " +
                "productId, " +
                "amount, " +
                "productionCost) VALUES (?, ?, ?, ?);";

        for(int i = 0; i < produces.length; i++){

            Produce target = produces[i];

            try{
                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                prep_statement.setInt(1, target.getFactoryId());
                prep_statement.setInt(2, target.getProductId());
                prep_statement.setInt(3, target.getAmount());
                prep_statement.setInt(4, target.getProductionCost());
                prep_statement.executeUpdate();
                number_of_produce++;
                prep_statement.close();
            }catch (SQLException e) {
                e.printStackTrace();
            }

        }

        return number_of_produce;
    }


    /**
     * Should insert an array of Shipment into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertShipment(Shipment[] shipments) {
        int number_of_produce = 0;
        String insert_query = "INSERT INTO Shipment(" +
                "factoryId, " +
                "productId, " +
                "amount, " +
                "pricePerUnit) VALUES (?, ?, ?, ?);";

        for(int i = 0; i < shipments.length; i++){

            Shipment target = shipments[i];

            try{
                PreparedStatement prep_statement = this.connection.prepareStatement(insert_query);
                prep_statement.setInt(1, target.getFactoryId());
                prep_statement.setInt(2, target.getProductId());
                prep_statement.setInt(3, target.getAmount());
                prep_statement.setInt(4, target.getPricePerUnit());
                prep_statement.executeUpdate();
                number_of_produce++;
                prep_statement.close();
            }catch (SQLException e) {
                e.printStackTrace();
            }

        }

        return number_of_produce;
    }

    /**
     * Should return all factories that are located in a particular country.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesForGivenCountry(String country) {
        ResultSet res;
        ArrayList<Factory> temp = new ArrayList<>();
        String query =  "SELECT DISTINCT fac.factoryId, fac.factoryName, fac.factoryType, fac.country " +
                        "FROM Factory fac " +
                        "WHERE fac.country = \"" + country +
                        "\" ORDER BY fac.factoryId ASC;";
        try{
            Statement statement = this.connection.createStatement();
            res = statement.executeQuery(query);

            while(res.next()){
                int factoryId = res.getInt("factoryId");
                String resfactoryName = res.getString("factoryName") ;
                String resfactoryType = res.getString("factoryType");
                String resCountry = res.getString("country");
                temp.add(new Factory(factoryId, resfactoryName, resfactoryType, resCountry));
            }
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        Factory[] factory_array =  new Factory[temp.size()];

        for(int i = 0; i < temp.size(); i++){
            factory_array[i] = temp.get(i);
        }
        return factory_array;
    }



    /**
     * Should return all factories without any working employees.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesWithoutAnyEmployee() {

        ResultSet res;
        ArrayList<Factory> temp = new ArrayList<>();
        String query =  "SELECT DISTINCT fac.factoryId, fac.factoryName, fac.factoryType, fac.country " +
                        "FROM Factory fac " +
                        "WHERE NOT EXISTS (SELECT 1 FROM Works_In W WHERE W.factoryId = fac.factoryId) " +
                        "ORDER BY fac.factoryId ASC;";

        try {
            Statement statement = this.connection.createStatement();
            res = statement.executeQuery(query);

            while (res.next()) {
                int factoryId = res.getInt("factoryId");
                String resfactoryName = res.getString("factoryName");
                String resfactoryType = res.getString("factoryType");
                String resCountry = res.getString("country");
                temp.add(new Factory(factoryId, resfactoryName, resfactoryType, resCountry));
            }
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Factory[] factoryArray = new Factory[temp.size()];

        for (int i = 0; i < temp.size(); i++) {
            factoryArray[i] = temp.get(i);
        }
        return factoryArray;
        //return new Factory[0];
    }

    /**
     * Should return all factories that produce all products for a particular productType
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesProducingAllForGivenType(String productType) {

        ResultSet res;
        ArrayList<Factory> temp = new ArrayList<>();

        String query =  "SELECT DISTINCT fac.factoryId, fac.factoryName, fac.factoryType, fac.country " +
                        "FROM Factory fac " +
                        "WHERE NOT EXISTS " +
                            "(SELECT puct.productId " +
                            "FROM Product puct " +
                            "WHERE puct.productType = \"" + productType + "\"" + "AND NOT EXISTS " +
                                "(SELECT puce2.factoryId " +
                                "FROM Produce puce2 " +
                                "WHERE puce2.factoryId = fac.factoryId AND puce2.productId = puct.productId)) " +
                        "ORDER BY fac.factoryId ASC;";
        try{
            Statement statement = this.connection.createStatement();
            res = statement.executeQuery(query);

            while(res.next()){
                int factoryId = res.getInt("factoryId");
                String resfactoryName = res.getString("factoryName") ;
                String resfactoryType = res.getString("factoryType");
                String resCountry = res.getString("country");
                temp.add(new Factory(factoryId, resfactoryName, resfactoryType, resCountry));
            }
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        Factory[] factory_array =  new Factory[temp.size()];

        for(int i = 0; i < temp.size(); i++){
            factory_array[i] = temp.get(i);
        }
        return factory_array;


    }


    /**
     * Should return the products that are produced in a particular factory but
     * don’t have any shipment from that factory.
     *
     * @return Product[]
     */
    public Product[] getProductsProducedNotShipped() {

        ResultSet res;
        ArrayList<Product> temp = new ArrayList<>();

        String query =  "SELECT DISTINCT puct.productId, puct.productName, puct.productType " +
                        "FROM Product puct, Produce puce " +
                        "WHERE puct.productId = puce.productId " + "AND NOT EXISTS " +
                            "(SELECT * " +
                            "FROM Shipment s " +
                            "WHERE s.productId = puce.productId AND s.factoryId = puce.factoryId) " +
                        "ORDER BY puct.productId ASC;";

        try{
            Statement statement = this.connection.createStatement();
            res = statement.executeQuery(query);

            while(res.next()){
                int productId = res.getInt("productId");
                String resproductName = res.getString("productName") ;
                String resproductType = res.getString("productType");
                temp.add(new Product(productId, resproductName, resproductType));
            }
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }

        Product[] product_array =  new Product[temp.size()];

        for(int i = 0; i < temp.size(); i++){
            product_array[i] = temp.get(i);
        }
        return product_array;
    }


    /**
     * For a given factoryId and department, should return the average salary of
     *     the employees working in that factory and that specific department.
     *
     * @return double
     */
    public double getAverageSalaryForFactoryDepartment(int factoryId, String department) {

        ResultSet res;
        double avg_sal = 0;

        String query =  "SELECT AVG(e.salary) AS avg_sal " +
                        "FROM Employee e, Works_In w " +
                        "WHERE e.employeeId = w.employeeId AND w.factoryId = " + factoryId  + " " +
                                "AND e.department = \"" +department + "\"" +
                                "GROUP BY w.factoryId, e.department;";

        try {
            Statement statement = this.connection.createStatement();
            res = statement.executeQuery(query);

            if (res.next()) {
                avg_sal = res.getDouble("avg_sal");
            }

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return avg_sal;
    }


    /**
     * Should return the most profitable products for each factory
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProducts() {
        ResultSet res;
        ArrayList<QueryResult.MostValueableProduct> temp = new ArrayList<>();

        //String query =

        String query =  "SELECT table1.factoryId, table1.productId, puct.productName, puct.productType, " +
                                "table1.profit " +
                        "FROM Product puct, " +
                            "(SELECT puce.factoryId, puce.productId, " +
                                "(s.amount * s.pricePerUnit - puce.amount * puce.productionCost) AS profit " +
                            "FROM Shipment s, Product puct, Produce puce " +
                            "WHERE puce.factoryId = s.factoryId " +
                            "AND puce.productId = s.productId " +


                            "UNION " +

                            "SELECT puce2.factoryId, puce2.productId, " +
                                    "(- puce2.amount * puce2.productionCost) as profit " +
                            "FROM Product puct2, Produce puce2 " +
                            "WHERE puct2.productId = puce2.productId " + "AND NOT EXISTS " +
                                "(SELECT * " +
                                "FROM Shipment s " +
                                "WHERE s.productId = puce2.productId AND s.factoryId = puce2.factoryId)) as table1, " +

                            "(SELECT table1.factoryId, table1.productId, " +
                                    "MAX(table1.profit) as max_profit " +
                            "FROM " +
                                "(SELECT puce.factoryId, puce.productId, " +
                                    "(s.amount * s.pricePerUnit - puce.amount * puce.productionCost) AS profit " +
                                "FROM Shipment s, Product puct, Produce puce " +
                                "WHERE puce.factoryId = s.factoryId " +
                                "AND puce.productId = s.productId " +

                                "UNION " +

                                "SELECT puce2.factoryId, puce2.productId, " +
                                        "(- puce2.amount * puce2.productionCost) as profit " +
                                "FROM Product puct2, Produce puce2 " +
                                "WHERE puct2.productId = puce2.productId " + "AND NOT EXISTS " +
                                    "(SELECT * " +
                                    "FROM Shipment s " +
                                    "WHERE s.productId = puce2.productId AND s.factoryId = puce2.factoryId)) as table1 " +
                            "GROUP BY table1.factoryId) as max_table " +
                        "WHERE puct.productId = table1.productId " +
                        "AND table1.profit  = max_table.max_profit " +
                        "AND table1.factoryId = max_table.factoryId " +
                        "ORDER BY table1.profit DESC, table1.factoryId ASC;";



        try {
            Statement statement = this.connection.createStatement();
            res = statement.executeQuery(query);

            while (res.next()) {
                int factoryId = res.getInt("factoryId");
                int productId = res.getInt("productId");
                String productName = res.getString("productName");
                String productType = res.getString("productType");
                double profit = res.getDouble("profit");

                temp.add(new QueryResult.MostValueableProduct(factoryId, productId, productName, productType, profit));
                //temp.add(new QueryResult.MostValueableProduct(factoryId, 10, "sex", "bok",profit));
            }

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.MostValueableProduct[] ProfitArray = new QueryResult.MostValueableProduct[temp.size()];

        for (int i = 0; i < temp.size(); i++) {
            ProfitArray[i] = temp.get(i);
        }

        return ProfitArray;
    }

    /**
     * For each product, return the factories that gather the highest profit
     * for that product
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProductsOnFactory() {
        ResultSet res;
        ArrayList<QueryResult.MostValueableProduct> temp = new ArrayList<>();

        /*String query = "SELECT s.factoryId, s.productId, " + "MAX(s.amount * s.pricePerUnit - puce.amount * puce.productionCost) AS profit, " +
                            "(SELECT productName FROM Product p WHERE p.productId = s.productId) AS productName, " +
                            "(SELECT productType FROM Product p WHERE p.productId = s.productId) AS productType " +
                        "FROM Shipment s, Produce puce " +
                        "WHERE s.factoryId = puce.factoryId AND s.productId = puce.productId " +
                        "GROUP BY s.factoryId, s.productId " +
                        "ORDER BY profit DESC, s.productId ASC;";*/

        String query =  "SELECT table1.factoryId, table1.productId, puct.productName, puct.productType, " +
                                "table1.profit " +
                        "FROM Product puct, " +
                            "(SELECT puce.factoryId, puce.productId, " +
                                "(s.amount * s.pricePerUnit - puce.amount * puce.productionCost) AS profit " +
                            "FROM Shipment s, Product puct, Produce puce " +
                            "WHERE puce.factoryId = s.factoryId " +
                            "AND puce.productId = s.productId " +


                            "UNION " +

                            "SELECT puce2.factoryId, puce2.productId, " +
                                "(- puce2.amount * puce2.productionCost) as profit " +
                            "FROM Product puct2, Produce puce2 " +
                            "WHERE puct2.productId = puce2.productId " + "AND NOT EXISTS " +
                                "(SELECT * " +
                                "FROM Shipment s " +
                                "WHERE s.productId = puce2.productId AND s.factoryId = puce2.factoryId)) as table1, " +

                            "(SELECT table1.factoryId, table1.productId, " +
                                    "MAX(table1.profit) as max_profit " +
                            "FROM " +
                                "(SELECT puce.factoryId, puce.productId, " +
                                    "(s.amount * s.pricePerUnit - puce.amount * puce.productionCost) AS profit " +
                                "FROM Shipment s, Product puct, Produce puce " +
                                "WHERE puce.factoryId = s.factoryId " +
                                "AND puce.productId = s.productId " +

                                "UNION " +

                                "SELECT puce2.factoryId, puce2.productId, " +
                                    "(- puce2.amount * puce2.productionCost) as profit " +
                                "FROM Product puct2, Produce puce2 " +
                                "WHERE puct2.productId = puce2.productId " + "AND NOT EXISTS " +
                                    "(SELECT * " +
                                    "FROM Shipment s " +
                                    "WHERE s.productId = puce2.productId AND s.factoryId = puce2.factoryId)) as table1 " +
                            "GROUP BY table1.productId) as max_table " +
                        "WHERE puct.productId = table1.productId " +
                        "AND table1.profit  = max_table.max_profit " +
                        "AND table1.productId = max_table.productId " +
                        "ORDER BY table1.profit DESC, table1.factoryId ASC;";

        try {
            Statement statement = this.connection.createStatement();
            res = statement.executeQuery(query);

            while (res.next()) {
                int factoryId = res.getInt("factoryId");
                int productId = res.getInt("productId");
                double profit = res.getDouble("profit");
                String productName = res.getString("productName");
                String productType = res.getString("productType");

                temp.add(new QueryResult.MostValueableProduct(factoryId, productId, productName, productType, profit));
            }

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return temp.toArray(new QueryResult.MostValueableProduct[0]);
    }


    /**
     * For each department, should return all employees that are paid under the
     *     average salary for that department. You consider the employees
     *     that do not work earning ”0”.
     *
     * @return QueryResult.LowSalaryEmployees[]
     */
    public QueryResult.LowSalaryEmployees[] getLowSalaryEmployeesForDepartments() {
        ArrayList<QueryResult.LowSalaryEmployees> lowSalaryEmployees = new ArrayList<>();

        String query =  "SELECT * " +
                        "FROM " +
                        "(SELECT DISTINCT e.employeeId, e.employeeName, e.department, e.salary " +
                            "FROM Employee e, " +
                                "(SELECT e1.department, AVG(e1.salary) AS avg_salary " +
                                "FROM Works_In w1, Employee e1 " +
                                "GROUP BY e1.department) AS avg_sal " +
                            "WHERE e.department = avg_sal.department " +
                            "AND e.salary < avg_sal.avg_salary " +
                            "ORDER BY e.employeeId ASC)  as table_1 " +
                        "UNION " +
                        "SELECT * " +
                        "FROM " +
                            "(SELECT DISTINCT e1.employeeId, e1.employeeName, e1.department, 0 " +
                            "FROM Employee e1 " +
                            "WHERE NOT EXISTS " +
                                "(SELECT w1.employeeId " +
                                "FROM Works_In w1 " +
                                "WHERE e1.employeeId = w1.employeeId) " +
                            "ORDER BY e1.employeeId ASC) as table_2;";

                        /*"SELECT DISTINCT e.employeeId, e.employeeName, e.department, e.salary " +
                        "FROM Employee e, " +
                             "(SELECT new_emp.department, AVG(new_emp.true_sal) as avg_salary " +
                             "FROM " +
                                 "(SELECT with_zero.employeeId, with_zero.department, MIN(with_zero.salary) AS true_sal " +
                                 "FROM " +
                                    "((SELECT * FROM " +
                                    "(SELECT e1.employeeId, e1.department, e1.salary " +
                                    "FROM Employee e1) as a) " +
                                    //"GROUP BY e1.department " +

                                    "UNION " +
                                    "(SELECT * FROM " +
                                    "(SELECT e1.employeeId, e1.department, 0 " +
                                    "FROM Employee e1 " +
                                    "WHERE NOT EXISTS " +
                                //" " +
                                        "(SELECT w1.employeeId " +
                                        "FROM Works_In w1 " +
                                        "WHERE e1.employeeId = w1.employeeId)) as b)) as with_zero " +
                                 "GROUP BY with_zero.employeeId) as new_emp " +

                             "GROUP BY new_emp.department) as avg_emp " +
                        "WHERE e.department = avg_emp.department " +
                        "AND e.salary < avg_emp.avg_salary " +
                        "ORDER BY e.employeeId ASC;";*/




        try {
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            while (resultSet.next()) {
                QueryResult.LowSalaryEmployees lowSalaryEmployee = new QueryResult.LowSalaryEmployees(
                        resultSet.getInt("employeeId"),
                        resultSet.getString("employeeName"),
                        resultSet.getString("department"),
                        resultSet.getInt("salary")
                );
                lowSalaryEmployees.add(lowSalaryEmployee);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return lowSalaryEmployees.toArray(new QueryResult.LowSalaryEmployees[lowSalaryEmployees.size()]);
    }


    /**
     * For the products of given productType, increase the productionCost of every unit by a given percentage.
     *
     * @return number of rows affected
     */
    public int increaseCost(String productType, double percentage) {
        String updateQuery = "UPDATE Produce p " +
                "SET p.productionCost = p.productionCost *" + (1 + percentage/100)  +
                "WHERE p.productId IN (SELECT productId FROM Product WHERE productType = \"" + productType + "\");";

        /*String updateQuery = "UPDATE Produce p " +
                "SET p.productionCost = p.productionCost + (p.productionCost * " + percentage + ") "+
                "WHERE p.productId IN (SELECT productId FROM Product pr WHERE pr.productType = \"" + productType + "\" ;";*/

        int rowsAffected = 0;

        try {
            Statement statement = this.connection.createStatement();
            rowsAffected = statement.executeUpdate(updateQuery);
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return rowsAffected;
    }


    /**
     * Deleting all employees that have not worked since the given date.
     *
     * @return number of rows affected
     */
    public int deleteNotWorkingEmployees(String givenDate) {

        String delete_query = "DELETE FROM Employee WHERE employeeId NOT IN (" +
                "SELECT employeeId FROM Works_In WHERE startDate >= '" + givenDate + "');";


        try{
            Statement statement = this.connection.createStatement();
            return statement.executeUpdate(delete_query);
            //statement.close();
        }catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }

    }





    /**
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     *  THE METHODS AFTER THIS LINE WILL NOT BE GRADED.
     *  YOU DON'T HAVE TO SOLVE THEM, LEAVE THEM AS IS IF YOU WANT.
     *  IF YOU HAVE ANY QUESTIONS, REACH ME VIA EMAIL.
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     */

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Peers are considered tied and receive the same rank. After
     * that, there should be a gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Everything is the same but after ties, there should be no
     * gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank2() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each factory, calculate the most profitable 4th product.
     *
     * @return QueryResult.FactoryProfit
     */
    public QueryResult.FactoryProfit calculateFourth() {
        return new QueryResult.FactoryProfit(0,0,0);
    }

    /**
     * Determine the salary variance between an employee and another
     * one who began working immediately after the first employee (by
     * startDate), for all employees.
     *
     * @return QueryResult.SalaryVariant[]
     */
    public QueryResult.SalaryVariant[] calculateVariance() {
        return new QueryResult.SalaryVariant[0];
    }

    /**
     * Create a method that is called once and whenever a Product starts
     * losing money, deletes it from Produce table
     *
     * @return void
     */
    public void deleteLosing() {

    }

    /*public void printTableData(String tableName) {
        try (Statement statement = connection.createStatement()) {
            String query = "SELECT * FROM " + tableName;
            ResultSet resultSet = statement.executeQuery(query);

            System.out.println("Data in " + tableName + " table:");
            while (resultSet.next()) {
                // Print or process each column value
                System.out.println("Column1: " + resultSet.getString("column1") + ", Column2: " + resultSet.getString("column2"));
                // Repeat for other columns
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }*/
}
